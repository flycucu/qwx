// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

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
    // TODO: webwx use json as HTTP POST
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    if (needSetCookie) {
        QFile file(QWXDIR + "/cookies");
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QList<QNetworkCookie> cookies = QNetworkCookie::parseCookies(out.readAll().toUtf8());
            QVariant var;
            var.setValue(cookies);
            request.setHeader(QNetworkRequest::CookieHeader, var);
        }
    }
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), 
            this, SLOT(m_finished(QNetworkReply*)));
    connect(&m_nam, &QNetworkAccessManager::sslErrors, 
            this, &HttpPost::m_sslErrors);
    m_nam.post(request, str.toUtf8());
}

void HttpPost::finished(QNetworkReply*) {}

void HttpPost::m_finished(QNetworkReply* reply) 
{
    this->finished(reply);
    disconnect(&m_nam, SIGNAL(finished(QNetworkReply*)), 
               this, SLOT(m_finished(QNetworkReply*)));
    disconnect(&m_nam, &QNetworkAccessManager::sslErrors, 
               this, &HttpPost::m_sslErrors);
}

void HttpPost::m_sslErrors(QNetworkReply* reply, const QList<QSslError> & errors) 
{
    reply->ignoreSslErrors(errors);
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << reply << errors;
#endif
}
