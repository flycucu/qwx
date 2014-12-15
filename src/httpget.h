// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

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

    QList<QNetworkCookie> cookies() const;
    void get(QString url, bool needSetCookie = false);

protected:
    virtual void finished(QNetworkReply* reply);

private Q_SLOTS:
    void m_finished(QNetworkReply* reply);
    void m_sslErrors(QNetworkReply* reply, const QList<QSslError> & errors);

private:
    QNetworkAccessManager m_nam;
    QString m_url;
    QList<QNetworkCookie> m_cookies;
};

#endif // HTTP_GET_H
