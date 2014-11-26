// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef COOKIE_H
#define COOKIE_H

#include "httpget.h"

class Cookie : public HttpGet 
{
    Q_OBJECT

    Q_PROPERTY(QVariant cookies READ cookies)

public:
    Cookie(HttpGet* parent = nullptr);
    ~Cookie();

    QVariant cookies() const;

    Q_INVOKABLE void get(QString redirect_uri);

Q_SIGNALS:
    void infoChanged(QString uin, QString sid);

protected:
    void finished(QNetworkReply* reply);
};

#endif // COOKIE_H
