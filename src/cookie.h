// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef COOKIE_H
#define COOKIE_H

#include "httpget.h"

class Cookie : public HttpGet 
{
    Q_OBJECT

public:
    Cookie(HttpGet* parent = nullptr);
    ~Cookie();

    Q_INVOKABLE void get(QString redirect_uri);
    Q_INVOKABLE void getV2(QString redirect_uri);

Q_SIGNALS:
    void infoChanged(QString uin, QString sid, QString ticket);
    void switchToV2();

protected:
    void finished(QNetworkReply* reply);
};

#endif // COOKIE_H
