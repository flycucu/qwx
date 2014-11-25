// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include "headimg.h"
#include "globaldeclarations.h"

HeadImg::HeadImg(HttpGet* parent) 
  : HttpGet(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

HeadImg::~HeadImg() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void HeadImg::get(QString userName) 
{
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxgeticon?seq=1388335457"
        "&username=" + userName;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url);
}

void HeadImg::finished(QNetworkReply* reply) 
{
    QString replyStr(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
}
