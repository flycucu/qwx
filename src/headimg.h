// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef HEAD_IMG_H
#define HEAD_IMG_H

#include "httpget.h"

class HeadImg : public HttpGet 
{
    Q_OBJECT

public:
    HeadImg(HttpGet* parent = nullptr);
    ~HeadImg();

    Q_INVOKABLE void get(QString userName);

Q_SIGNALS:
    void cache(QString filePath);

protected:
    void finished(QNetworkReply* reply);
};

#endif // HEAD_IMG_H
