// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef IP_CITY_H
#define IP_CITY_H

#include "httpget.h"

class IpCity : public HttpGet 
{
    Q_OBJECT

public:
    IpCity(HttpGet* parent = nullptr);
    ~IpCity();

    Q_INVOKABLE void get();

Q_SIGNALS:
    void cityChanged(QString city);

protected:
    void finished(QNetworkReply* reply);
};

#endif // IP_CITY_H
