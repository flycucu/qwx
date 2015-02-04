// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QNetworkCookie>

#include "httppost.h"
#include "globaldeclarations.h"

HttpPost::HttpPost(QObject* parent) 
  : QObject(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

HttpPost::~HttpPost() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void HttpPost::post(QString url, QString str, bool needSetCookie) 
{
    QNetworkRequest request(url);
    
    // webwx use json content type as HTTP POST header
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (needSetCookie) {
        QFile file(QWXDIR + "/" + COOKIE_FILENAME);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QList<QNetworkCookie> cookies = QNetworkCookie::parseCookies(out.readAll().toUtf8());
            QVariant var;
            var.setValue(cookies);
            request.setHeader(QNetworkRequest::CookieHeader, var);
        }
    }
    
    m_sslErrorConnection = connect(&m_nam, &QNetworkAccessManager::sslErrors, 
            [this](QNetworkReply* reply, const QList<QSslError> & errors) {
                reply->ignoreSslErrors(errors);
            });
    m_finishConnection = connect(&m_nam, &QNetworkAccessManager::finished, 
            [this](QNetworkReply* reply) {
                emit signalFinished(reply);
                this->finished(reply);
                disconnect(m_sslErrorConnection);
                disconnect(m_finishConnection);
            });
    
    m_nam.post(request, str.toUtf8());
}
