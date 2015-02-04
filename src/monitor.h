// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef MONITOR_H
#define MONITOR_H

#include "httpget.h"

class Monitor : public HttpGet 
{
    Q_OBJECT

public:
    Monitor(HttpGet* parent = nullptr);
    ~Monitor();

    Q_INVOKABLE void get(QString uin, 
                         QString sid, 
                         QString skey, 
                         QString deviceId, 
                         QStringList syncKey);
    Q_INVOKABLE void getV2(QString uin,                                              
                         QString sid,                                              
                         QString skey,                                             
                         QString deviceId,                                         
                         QStringList syncKey);

Q_SIGNALS:
    void noNewMsg();
    void newMsg();

protected:
    void finished(QNetworkReply* reply);

private:
    void m_get(QString host, 
               QString uin, 
               QString sid, 
               QString skey, 
               QString deviceId, 
               QStringList syncKey);
};

#endif // MONITOR_H
