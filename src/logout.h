// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef LOGOUT_H
#define LOGOUT_H

#include "httpget.h"

class LogOut : public HttpGet
{
    Q_OBJECT

public:
    LogOut(HttpGet* parent = nullptr);
    ~LogOut();

    Q_INVOKABLE void get();
    Q_INVOKABLE void getV2();

private:
    void m_get(QString host);
};

#endif // LOGOUT_H
