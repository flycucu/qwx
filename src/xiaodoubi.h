// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef XIAODOUBI_H
#define XIAODOUBI_H

#include "httpget.h"
#include "idiom.h"

class XiaoDouBi : public HttpGet 
{
    Q_OBJECT

public:
    XiaoDouBi(HttpGet* parent = nullptr);
    ~XiaoDouBi();

    Q_INVOKABLE void get(QString word);

Q_SIGNALS:
    void contentChanged(QString content);

protected:
    void finished(QNetworkReply* reply);

private:
    Idiom m_idiom;
};

#endif // XIAODOUBI_H
