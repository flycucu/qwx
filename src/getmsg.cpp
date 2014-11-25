// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include "getmsg.h"
#include "globaldeclarations.h"

GetMsg::GetMsg(HttpPost* parent) 
  : HttpPost(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

GetMsg::~GetMsg() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void GetMsg::post(QString uin, QString sid) 
{
    QString ts = QString::number(time(NULL));
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxsync?sid=" + sid + "&r=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":" + uin + ",\"Sid\":\"" + sid 
        + "\"},\"SyncKey\":{\"Count\":5,\"List\":[{\"Key\":1,\"Val\":620916854}"
        ",{\"Key\":2,\"Val\":620917978},{\"Key\":3,\"Val\":620917975}"
        ",{\"Key\":201,\"Val\":1388977392},{\"Key\":1000,\"Val\":1388967977}]},"
        "\"rr\":" + ts + "}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json);
}

void GetMsg::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
}
