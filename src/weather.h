// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef WEATHER_H
#define WEATHER_H

#include "httpget.h"

class Weather : public HttpGet 
{
    Q_OBJECT

public:
    Weather(HttpGet* parent = nullptr);
    ~Weather();

    Q_INVOKABLE void get(QString city);

Q_SIGNALS:
    void weatherChanged(QString report);

protected:
    void finished(QNetworkReply* reply);

private:
    QString m_city;
};

#endif // WEATHER_H
