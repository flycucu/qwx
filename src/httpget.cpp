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

void HttpGet::get(QString url, bool needSetCookie) 
{
    QNetworkRequest request(url);

    m_url = url;
    // load cookie
    if (needSetCookie) { 
        QFile file(QWXDIR + "/" + COOKIE_FILENAME);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QList<QNetworkCookie> cookies = 
                QNetworkCookie::parseCookies(out.readAll().toUtf8());
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
                m_cookies = m_nam.cookieJar()->cookiesForUrl(QUrl(m_url));
                // overloaded by inhertied class object
                this->finished(reply);
                disconnect(m_sslErrorConnection);
                disconnect(m_finishConnection);
            });
    m_nam.get(request);
}
