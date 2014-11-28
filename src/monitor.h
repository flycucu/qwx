// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef MONITOR_H
#define MONITOR_H

#include "httpget.h"

class Monitor : public HttpGet 
{
    Q_OBJECT

public:
    Monitor(HttpGet* parent = nullptr);
    ~Monitor();

    Q_INVOKABLE void get(QString uin, QString sid);

Q_SIGNALS:
    void messaged(QString uuid);

protected:
    void finished(QNetworkReply* reply);
};

#endif // MONITOR_H
