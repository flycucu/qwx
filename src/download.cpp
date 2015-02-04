// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

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

    // webwx download file need cookie
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
    
    m_sslErrorConnection = connect(&m_nam, &QNetworkAccessManager::sslErrors, 
            [this](QNetworkReply* reply, const QList<QSslError> & errors) {
                reply->ignoreSslErrors(errors);
            });
    
    m_reply = m_nam.get(request);
    
    m_downloadProgressConnection = connect(m_reply, &QNetworkReply::downloadProgress, 
            [this](qint64 bytesReceived, qint64 bytesTotal) {
                if (bytesTotal)
                    emit downloaded(bytesReceived / bytesTotal);
            });
    m_readyReadConnection = connect(m_reply, &QNetworkReply::readyRead, 
            [this] {
                m_file.write(m_reply->readAll());
                m_file.flush();
            });
    m_finishConnection = connect(&m_nam, &QNetworkAccessManager::finished, 
            [this] {
                emit finished();
                disconnect(m_downloadProgressConnection);
                disconnect(m_readyReadConnection);
                disconnect(m_sslErrorConnection);
                disconnect(m_finishConnection);
            });
}
