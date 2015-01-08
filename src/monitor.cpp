// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

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

void Monitor::get(QString uin, 
                  QString sid, 
                  QString skey, 
                  QString deviceId, 
                  QStringList syncKey) 
{
    if (syncKey.size() != 5) { emit error(); return; }
    
    QString ts = QString::number(time(NULL));
    QString url = "https://webpush.weixin.qq.com" + WX_CGI_PATH + 
        "synccheck?skey=" + skey + 
        "&callback=jQuery18308660551080269895_1388975862078&r=" + ts + 
        "&sid=" + sid + "&uin=" + uin + "&deviceid=" + deviceId + 
        "&synckey=1_" + syncKey[0] + "%7C2_" + syncKey[1] + "%7C3_" + 
        syncKey[2] + "%7C11_" + syncKey[3] + "%7C1000_" + syncKey[4] + "&_=" + 
        ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url, true);
}

void Monitor::getV2(QString uin,                                                     
                  QString sid,                                                     
                  QString skey,                                                    
                  QString deviceId,                                                
                  QStringList syncKey)                                             
{                                                                                  
    if (syncKey.size() != 5) { emit error(); return; }                             
                                                                                   
    QString ts = QString::number(time(NULL));                                      
    QString url = "https://webpush2.weixin.qq.com" + WX_CGI_PATH +                  
        "synccheck?skey=" + skey +                                                 
        "&callback=jQuery183008612365838727565_1397377003545&r=" + ts +             
        "&sid=" + sid + "&uin=" + uin + "&deviceid=" + deviceId +                  
        "&synckey=1_" + syncKey[0] + "%7C2_" + syncKey[1] + "%7C3_" +              
        syncKey[2] + "%7C11_" + syncKey[3] + "%7C1000_" + syncKey[4] + "&_=" +   
        ts;                                                                        
#if QWX_DEBUG                                                                      
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;                            
#endif                                                                             
    HttpGet::get(url, true);                                                       
}

void Monitor::finished(QNetworkReply* reply) 
{
    QString replyStr(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
    
    if (replyStr != "window.synccheck={retcode:\"0\",selector:\"0\"}") {
        qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << "needReSync";
        emit needReSync(); 
        return;
    }
}
