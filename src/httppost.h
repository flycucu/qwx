// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef HTTP_POST_H
#define HTTP_POST_H

#include <QObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>

class HttpPost : public QObject 
{
    Q_OBJECT

public:
    HttpPost(QObject* parent = nullptr);
    virtual ~HttpPost();

public:
    void post(QString url, QString str, bool needSetCookie = false);

Q_SIGNALS:
    void signalFinished(QNetworkReply* reply);

protected:
    virtual void finished(QNetworkReply* reply) { Q_UNUSED(reply); }

private:
    QNetworkAccessManager m_nam;
    QMetaObject::Connection m_sslErrorConnection;
    QMetaObject::Connection m_finishConnection;
};

#endif // HTTP_POST_H
