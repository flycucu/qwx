// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include "monitor.h"
#include "globaldeclarations.h"

Monitor::Monitor(HttpGet* parent) 
  : HttpGet(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

Monitor::~Monitor() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void Monitor::get(QString uin, QString sid) 
{
    QString ts = QString::number(time(NULL));
    // FIXME: SyncKey
    QString url = "https://webpush.weixin.qq.com" + WX_CGI_PATH + 
        "synccheck?callback=jQuery18308660551080269895_1388975862078&r=" + ts + 
        "&sid=" + sid + "&uin=" + uin + "&deviceid=" + DEVICE_ID + 
        "&synckey=1_620916854%7C2_620917963%7C3_620917948%7C201_1388976090%7C"
        "1000_1388967977&_=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url);
}

void Monitor::finished(QNetworkReply* reply) 
{
    QString replyStr(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
}
