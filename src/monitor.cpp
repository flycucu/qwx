// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#if QWX_DEBUG
#include <QFile>
#endif
#include <time.h>

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

void Monitor::m_get(QString host, 
                    QString uin, 
                    QString sid, 
                    QString skey, 
                    QString deviceId, 
                    QStringList syncKey) 
{
    QString ts = QString::number(time(NULL));
    QString url = host + WX_CGI_PATH + "synccheck?skey=" + skey + 
        "&callback=jQuery183084135492448695_1420782130686&r=" + ts + 
        "&sid=" + sid + "&uin=" + uin + "&deviceid=" + deviceId + 
        "&synckey=";
    for (int i = 0; i < syncKey.size(); i++) {
        if (i != 0)
            url += "%7C";
        QStringList result = syncKey[i].split("|");
        url += result[0] + "_" + result[1];
    }
    url += "&_=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url, true);
}

void Monitor::get(QString uin, 
                  QString sid, 
                  QString skey, 
                  QString deviceId, 
                  QStringList syncKey) 
{
    m_get("https://webpush.weixin.qq.com", uin, sid, skey, deviceId, syncKey);
}

void Monitor::getV2(QString uin,                                                     
                    QString sid,                                                     
                    QString skey,                                                    
                    QString deviceId,                                                
                    QStringList syncKey)
{                                                                                  
    m_get("https://webpush2.weixin.qq.com", uin, sid, skey, deviceId, syncKey);
}

void Monitor::finished(QNetworkReply* reply) 
{
    QString replyStr(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
    QFile file("synccheck.json"); 
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {                       
        QTextStream out(&file);                                                    
        out << replyStr;                                                           
        file.close();                                                              
    }
#endif
    
    if (replyStr != "window.synccheck={retcode:\"0\",selector:\"0\"}") {
        emit newMsg(); 
    } else {
        emit noMsg();
    }
}
