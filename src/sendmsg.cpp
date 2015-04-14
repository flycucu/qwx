// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
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

void SendMsg::m_saveLog(QString fromUserName, QString toUserName, QString content) 
{
    QFile file(QWXDIR + "/" + toUserName + ".txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QString::number(time(NULL)) << DELIM << fromUserName << DELIM 
            << content << "\n";
        file.close();
    }
}

void SendMsg::send(QString uin, 
                   QString sid, 
                   QString skey,
                   QString deviceId, 
                   QString fromUserName, 
                   QString toUserName, 
                   QString content, 
                   QStringList syncKey) 
{   
    m_saveLog(fromUserName, toUserName, content);
    post(uin, sid, skey, deviceId, fromUserName, toUserName, content);
    sync(uin, sid, skey, syncKey);
}

void SendMsg::sendV2(QString uin,
                   QString sid,
                   QString skey,
                   QString deviceId,
                   QString fromUserName,
                   QString toUserName,
                   QString content,
                   QStringList syncKey)
{
    m_saveLog(fromUserName, toUserName, content);
    postV2(uin, sid, skey, deviceId, fromUserName, toUserName, content);
    syncV2(uin, sid, skey, syncKey);
}

void SendMsg::m_post(QString host, 
                     QString uin, 
                     QString sid, 
                     QString skey, 
                     QString deviceId, 
                     QString fromUserName, 
                     QString toUserName, 
                     QString content)
{
    QString ts = QString::number(time(NULL));
    QString url = host + WX_CGI_PATH + "webwxsendmsg?sid=" + sid 
        + "&skey=" + skey + "&r=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":" + uin + ",\"Sid\":\"" + sid 
        + "\",\"Skey\":\"" + skey + "\",\"DeviceID\":\"" + deviceId 
        + "\"},\"Msg\":{\"FromUserName\":\"" + fromUserName 
        + "\",\"ToUserName\":\"" + toUserName 
        + "\",\"Type\":1,\"Content\":\"" + content.replace("\"", "\\\"") 
        + "\",\"ClientMsgId\":" + ts 
        + ",\"LocalID\":" + ts + "}}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json, true);
}

void SendMsg::post(QString uin, 
                   QString sid, 
                   QString skey, 
                   QString deviceId, 
                   QString fromUserName, 
                   QString toUserName, 
                   QString content)
{
    m_post(WX_SERVER_HOST, 
           uin, 
           sid, 
           skey, 
           deviceId, 
           fromUserName, 
           toUserName, 
           content);
}

void SendMsg::postV2(QString uin,
                     QString sid,
                     QString skey,
                     QString deviceId,
                     QString fromUserName,
                     QString toUserName,
                     QString content)
{
    m_post(WX_V2_SERVER_HOST, 
           uin, 
           sid, 
           skey, 
           deviceId, 
           fromUserName, 
           toUserName, 
           content);
}

void SendMsg::m_sync(QString host, 
                     QString uin, 
                     QString sid, 
                     QString skey, 
                     QStringList syncKey)
{                                                                                  
    QString ts = QString::number(time(NULL));                                      
    QString url = host + WX_CGI_PATH + "webwxsync?sid=" + sid +          
        "&skey=" + skey + "&r=" + ts;                                              
#if QWX_DEBUG                                                                      
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;                            
#endif                                                                             
    QString json = "{\"BaseRequest\":{\"Uin\":" + uin + ",\"Sid\":\"" + sid + 
        "\"},\"SyncKey\":{\"Count\":" + QString::number(syncKey.size()) + 
        ",\"List\":[";
    for (int i = 0; i < syncKey.size(); i++) {
        if (i != 0)
            json += ",";
        QStringList result = syncKey[i].split("|");
        json += "{\"Key\":" + result[0] + ",\"Val\":" + result[1] + "}";
    }
    json += "]},\"rr\":" + ts + "}";                                                 
#if QWX_DEBUG                                                                  
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;                           
#endif                                                                             
    HttpPost::post(url, json, true);                                               
}

void SendMsg::sync(QString uin, QString sid, QString skey, QStringList syncKey) 
{
    m_sync(WX_SERVER_HOST, uin, sid, skey, syncKey);
}

void SendMsg::syncV2(QString uin, QString sid, QString skey, QStringList syncKey)
{
    m_sync(WX_V2_SERVER_HOST, uin, sid, skey, syncKey);
}

void SendMsg::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
    QFile file("sendmsg.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {                       
        QTextStream out(&file);                                                    
        out << replyStr;                                                           
        file.close();                                                              
    }
#endif
}
