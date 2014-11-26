// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#if QWX_DEBUG
#include <QFile>
#endif
#include <QNetworkCookieJar>

#include "httpget.h"

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

void HttpGet::get(QString url) 
{
    m_url = url;
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), 
            this, SLOT(m_finished(QNetworkReply*)));
    connect(&m_nam, &QNetworkAccessManager::sslErrors, 
            this, &HttpGet::m_sslErrors);
    m_nam.get(QNetworkRequest(m_url));
}

void HttpGet::finished(QNetworkReply*) {}

void HttpGet::m_finished(QNetworkReply* reply) 
{
    this->finished(reply);
    m_cookies = m_nam.cookieJar()->cookiesForUrl(QUrl(m_url));
#if QWX_DEBUG
    QFile file("cookies");
    if (file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream out(&file);
        foreach (const QNetworkCookie cookie, m_cookies) {
            qDebug() << "DEBUG:" << cookie;
            QLocale locale = QLocale(QLocale::C, QLocale::AnyCountry);
            out << QString(cookie.name()) << "=" << QString(cookie.value()) 
                << "; expires=" << locale.toString(cookie.expirationDate(), "ddd, dd-MMM-yyyy hh:mm:ss") + " GMT" 
                << "; domain=" << cookie.domain() 
                << "; path=" << cookie.path() << endl;
        }
    }
#endif
    disconnect(&m_nam, SIGNAL(finished(QNetworkReply*)), 
               this, SLOT(m_finished(QNetworkReply*)));
}

void HttpGet::m_sslErrors(QNetworkReply* reply, const QList<QSslError> & errors) 
{
    reply->ignoreSslErrors(errors);
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << reply << errors;
#endif
}
