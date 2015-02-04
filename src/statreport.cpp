// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <time.h>

#include "statreport.h"
#include "globaldeclarations.h"

StatReport::StatReport(HttpPost* parent) 
  : HttpPost(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

StatReport::~StatReport() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void StatReport::firstRequestSuccess(QString uuid) 
{
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxstatreport?type=1&r=" + 
        QString::number(time(NULL));
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":0,\"Sid\":0},\"Count\":1,"
        "\"List\":[{\"Type\":1,\"Text\":\"" + WX_CGI_PATH 
        + "login, First Request Success, uuid: " + uuid + "\"}]}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json);
}

void StatReport::secondRequestStart(QString uuid) 
{
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxstatreport?type=1&r=" + 
        QString::number(time(NULL));
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":0,\"Sid\":0},\"Count\":1,"
        "\"List\":[{\"Type\":1,\"Text\":\"" + WX_CGI_PATH 
        + "login, Second Request Start, uuid: " + uuid + "\"}]}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json);
}

void StatReport::m_post(QString host, QString uuid) 
{
    QString url = host + WX_CGI_PATH + "webwxstatreport?type=1&r=" + 
        QString::number(time(NULL));
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":0,\"Sid\":0},\"Count\":1,"
        "\"List\":[{\"Type\":1,\"Text\":\"" + WX_CGI_PATH + "login, "
        "Second Request Success, uuid: " + uuid + ", time: 190765ms\"}]}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json, true);
}

void StatReport::post(QString uuid) { m_post(WX_SERVER_HOST, uuid); }

void StatReport::postV2(QString uuid) { m_post(WX_V2_SERVER_HOST, uuid); }

void StatReport::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
}
