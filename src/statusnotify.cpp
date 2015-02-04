// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <time.h>

#include "statusnotify.h"
#include "globaldeclarations.h"

StatusNotify::StatusNotify(HttpPost* parent) 
  : HttpPost(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

StatusNotify::~StatusNotify() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void StatusNotify::m_post(QString host, 
                          QString uin, 
                          QString sid, 
                          QString skey, 
                          QString deviceId, 
                          QString userName) 
{
    QString ts = QString::number(time(NULL));
    QString url = host + WX_CGI_PATH + "webwxstatusnotify?skey=" + skey + "&r=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":" + uin + ",\"Sid\":\"" + sid 
        + "\",\"Skey\":\"\",\"DeviceID\":\"" + deviceId + "\"},\"Code\":3,"
        "\"FromUserName\":\"" + userName + "\",\"ToUserName\":\"" + userName 
        + "\",\"ClientMsgId\":\"" + ts + "\"}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json, true);
}

void StatusNotify::post(QString uin, 
                        QString sid, 
                        QString skey, 
                        QString deviceId, 
                        QString userName) 
{
    m_post(WX_SERVER_HOST, uin, sid, skey, deviceId, userName);
}

void StatusNotify::postV2(QString uin,
                          QString sid,
                          QString skey,
                          QString deviceId,
                          QString userName)
{
    m_post(WX_V2_SERVER_HOST, uin, sid, skey, deviceId, userName);
}

void StatusNotify::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
}
