// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QNetworkCookieJar>

#include "httpget.h"
#include "globaldeclarations.h"

HttpGet::HttpGet(QObject* parent) 
  : QObject(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

HttpGet::~HttpGet() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

QList<QNetworkCookie> HttpGet::cookies() const { return m_cookies; }

void HttpGet::get(QString url, bool needSetCookie) 
{
    m_url = url;
    QNetworkRequest request(m_url);
    if (needSetCookie && m_cookies.size()) {
        QVariant var;                                                          
        var.setValue(m_cookies);                                                 
        request.setHeader(QNetworkRequest::CookieHeader, var);                 
    }
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), 
            this, SLOT(m_finished(QNetworkReply*)));
    connect(&m_nam, &QNetworkAccessManager::sslErrors, 
            this, &HttpGet::m_sslErrors);
    m_nam.get(request);
}

void HttpGet::finished(QNetworkReply*) {}

void HttpGet::m_finished(QNetworkReply* reply) 
{
    m_cookies = m_nam.cookieJar()->cookiesForUrl(QUrl(m_url));
    this->finished(reply);
    disconnect(&m_nam, SIGNAL(finished(QNetworkReply*)), 
               this, SLOT(m_finished(QNetworkReply*)));
    disconnect(&m_nam, &QNetworkAccessManager::sslErrors, 
               this, &HttpGet::m_finished);
}

void HttpGet::m_sslErrors(QNetworkReply* reply, const QList<QSslError> & errors) 
{
    reply->ignoreSslErrors(errors);
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << reply << errors;
#endif
}
