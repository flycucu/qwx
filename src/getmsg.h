// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef GET_MSG_H
#define GET_MSG_H

#include "httppost.h"

class GetMsg : public HttpPost 
{
    Q_OBJECT

public:
    GetMsg(HttpPost* parent = nullptr);
    ~GetMsg();

public:
    Q_INVOKABLE void post(QString uin, QString sid, QStringList syncKey);

Q_SIGNALS:
    void error();

protected:
    void finished(QNetworkReply* reply);
};

#endif // GET_MSG_H
