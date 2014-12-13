// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef QWXUUID_H
#define QWXUUID_H

#include "httpget.h"

class QwxUUID : public HttpGet
{
    Q_OBJECT

public:
    QwxUUID(HttpGet* parent = nullptr);
    ~QwxUUID();

    Q_INVOKABLE void get();

Q_SIGNALS:
    void error();
    void uuidChanged(QString uuid);

protected:
    void finished(QNetworkReply* reply);
};

#endif // QWXUUID_H
