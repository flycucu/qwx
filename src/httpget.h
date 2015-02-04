// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef HTTP_GET_H
#define HTTP_GET_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkCookie>

class HttpGet : public QObject 
{
    Q_OBJECT

public:
    HttpGet(QObject* parent = nullptr);
    virtual ~HttpGet();

    QList<QNetworkCookie> cookies() const { return m_cookies; }

    void get(QString url, bool needSetCookie = false);

protected:
    virtual void finished(QNetworkReply* reply) { Q_UNUSED(reply); }

private:
    QNetworkAccessManager m_nam;
    QString m_url;
    QList<QNetworkCookie> m_cookies;
    QMetaObject::Connection m_sslErrorConnection;
    QMetaObject::Connection m_finishConnection;
};

#endif // HTTP_GET_H
