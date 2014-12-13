// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <time.h>

#include "sendmsg.h"
#include "globaldeclarations.h"

SendMsg::SendMsg(HttpPost* parent) 
  : HttpPost(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

SendMsg::~SendMsg() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void SendMsg::send(QString uin, 
                   QString sid, 
                   QString skey, 
                   QString fromUserName, 
                   QString toUserName, 
                   QString content, 
                   QStringList syncKey) 
{   
    post(uin, sid, skey, fromUserName, toUserName, content);
    sync(uin, sid, skey, syncKey);
}

void SendMsg::post(QString uin, 
                   QString sid, 
                   QString skey, 
                   QString fromUserName, 
                   QString toUserName, 
                   QString content) 
{
    QString ts = QString::number(time(NULL));
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxsendmsg?sid=" + sid 
        + "&skey=" + skey + "&r=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":" + uin + ",\"Sid\":\"" + sid 
        + "\",\"Skey\":\"" + skey + "\",\"DeviceID\":\"" + DEVICE_ID 
        + "\"},\"Msg\":{\"FromUserName\":\"" + fromUserName 
        + "\",\"ToUserName\":\"" + toUserName 
        + "\",\"Type\":1,\"Content\":\"" + content + "\",\"ClientMsgId\":" + ts 
        + ",\"LocalID\":" + ts + "}}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json, true);
}

void SendMsg::sync(QString uin, QString sid, QString skey, QStringList syncKey) 
{                                                                                  
    if (syncKey.size() < 5) return;                                                
    QString ts = QString::number(time(NULL));                                      
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxsync?sid=" + sid +          
        "&skey=" + skey + "&r=" + ts;                                              
#if QWX_DEBUG                                                                      
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;                            
#endif                                                                             
    QString json = "{\"BaseRequest\":{\"Uin\":" + uin + ",\"Sid\":\"" + sid +   
        "\"},\"SyncKey\":{\"Count\":5,\"List\":[{\"Key\":1,\"Val\":" +             
        syncKey[0] + "},{\"Key\":2,\"Val\":" + syncKey[1] + "},{\"Key\":3,"        
        "\"Val\":" + syncKey[2] + "},{\"Key\":201,\"Val\":" +                      
        (syncKey.size() == 6 ? syncKey[4] : syncKey[3]) +                          
        "},{\"Key\":1000,\"Val\":" +                                               
        (syncKey.size() == 6 ? syncKey[5] : syncKey[4]) +                          
        "}]},\"rr\":" + ts + "}";                                                  
    #if QWX_DEBUG                                                                  
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;                           
#endif                                                                             
    HttpPost::post(url, json, true);                                               
}

void SendMsg::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
}
