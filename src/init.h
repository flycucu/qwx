// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef INIT_H
#define INIT_H

#include "httppost.h"

class Init : public HttpPost 
{
    Q_OBJECT

public:
    Init(HttpPost* parent = nullptr);
    ~Init();

    Q_INVOKABLE void post(QString uin, QString sid);

Q_SIGNALS:
    void error();
    void skeyChanged(QString skey);

protected:
    void finished(QNetworkReply* reply);
};

#endif // INIT_H
