// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#if QWX_DEBUG
#include <QFile>
#endif

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

void GetMsg::post(QString uin, QString sid, QStringList syncKey) 
{
    if (syncKey.size() != 5) { emit error(); return; }

    QString ts = QString::number(time(NULL));
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxsync?sid=" + sid + 
        "&r=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":" + uin + ",\"Sid\":\"" + sid 
        + "\"},\"SyncKey\":{\"Count\":5,\"List\":[{\"Key\":1,\"Val\":" + 
        syncKey[0] + "},{\"Key\":2,\"Val\":" + syncKey[1] + 
        "},{\"Key\":3,\"Val\":" + syncKey[2] + "},{\"Key\":201,\"Val\":" + 
        syncKey[3] + "},{\"Key\":1000,\"Val\":" + syncKey[4] + "}]},"
        "\"rr\":" + ts + "}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json, true);
}

void GetMsg::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
#if QWX_DEBUG
    QFile file("getmsg.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << replyStr;
        file.close(); 
    }
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;                                   
    qDebug() << "DEBUG:" << replyStr;                                              
#endif
}
