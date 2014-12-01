// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QDir>

#include "download.h"
#include "globaldeclarations.h"

Download::Download(QObject* parent) 
  : QObject(parent), 
    m_reply(nullptr)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

Download::~Download() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void Download::get(QString url, QString filePath) 
{
    QNetworkRequest request(url);
    QFile file(QWXDIR + "/" + COOKIE_FILENAME);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {                    
        QTextStream out(&file);                                                
        QList<QNetworkCookie> cookies = QNetworkCookie::parseCookies(
            out.readAll().toUtf8());
        QVariant var;                                                          
        var.setValue(cookies);                                                 
        request.setHeader(QNetworkRequest::CookieHeader, var);                 
    }
    
    m_file.setFileName(filePath);
    m_file.open(QIODevice::WriteOnly | QIODevice::Append);
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), 
            this, SLOT(m_finished(QNetworkReply*)));
    connect(&m_nam, &QNetworkAccessManager::sslErrors, 
            this, &Download::m_sslErrors);
    m_reply = m_nam.get(request);
    connect(m_reply, &QNetworkReply::downloadProgress, 
            this, &Download::m_downloadProgress);
    connect(m_reply, &QNetworkReply::readyRead, 
            this, &Download::m_readyRead);
}

void Download::m_downloadProgress(qint64 bytesReceived, qint64 bytesTotal) 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << m_file.fileName() 
             << bytesReceived << bytesTotal;
#endif
    if (bytesTotal) emit downloaded(bytesReceived / bytesTotal);
}

void Download::m_readyRead() 
{
    m_file.write(m_reply->readAll()); m_file.flush();
}

void Download::m_finished(QNetworkReply*) 
{
    disconnect(&m_nam, SIGNAL(finished(QNetworkReply*)), 
               this, SLOT(m_finished(QNetworkReply*)));
    disconnect(&m_nam, &QNetworkAccessManager::sslErrors, 
               this, &Download::m_sslErrors);
    disconnect(m_reply, &QNetworkReply::downloadProgress, 
               this, &Download::m_downloadProgress);
    emit finished();
}

void Download::m_sslErrors(QNetworkReply* reply, const QList<QSslError> & errors) 
{
    reply->ignoreSslErrors(errors);
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << reply << errors;
#endif
}
