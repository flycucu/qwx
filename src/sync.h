// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef SYNC_H
#define SYNC_H

#include "httppost.h"

class Sync : public HttpPost 
{
    Q_OBJECT

public:
    Sync(HttpPost* parent = nullptr);
    ~Sync();

    Q_INVOKABLE void post(QString uin, QString sid, QStringList synckey);

Q_SIGNALS:
    void error();

protected:
    void finished(QNetworkReply* reply);
};

#endif // SYNC_H
