// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef RMBZ_H
#define RMBZ_H

#include "httpget.h"

class Rmbz : public HttpGet 
{
    Q_OBJECT

public:
    Rmbz(HttpGet* parent = nullptr);
    ~Rmbz();

    Q_INVOKABLE void get(QString word);

Q_SIGNALS:
    void contentChanged(QString content);

protected:
    void finished(QNetworkReply* reply);
};

#endif // RMBZ_H
