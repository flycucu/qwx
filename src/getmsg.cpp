// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QJsonDocument>                                                           
#include <QJsonObject>                                                             
#include <QJsonArray>
#include <time.h>

#include "getmsg.h"
#include "globaldeclarations.h"

GetMsg::GetMsg(HttpPost* parent) 
  : HttpPost(parent), 
    m_fromUserName(""), 
    m_toUserName("") 
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

QString GetMsg::fromUserName() const { return m_fromUserName; }
void GetMsg::setFromUserName(const QString & fromUserName) 
{
    if (m_fromUserName != fromUserName) {
        m_fromUserName = fromUserName;
        emit fromUserNameChanged();
    }
}

QString GetMsg::toUserName() const { return m_toUserName; }
void GetMsg::setToUserName(const QString & toUserName) 
{
    if (m_toUserName != toUserName) {
        m_toUserName = toUserName;
        emit toUserNameChanged();
    }
}

QStringList GetMsg::syncKey() const { return m_syncKey; }

void GetMsg::post(QString uin, QString sid, QString skey, QStringList syncKey) 
{
    QString ts = QString::number(time(NULL));
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxsync?sid=" + sid + 
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

void GetMsg::postV2(QString uin, QString sid, QString skey, QStringList syncKey)
{
    QString ts = QString::number(time(NULL));
    QString url = WX_V2_SERVER_HOST + WX_CGI_PATH + "webwxsync?sid=" + sid + 
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

void GetMsg::m_saveLog(QString createTimeStr, QString fromUserName, QString content) 
{
    QFile file(QWXDIR + "/" + fromUserName + ".txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << createTimeStr << " " << fromUserName << " " << content << "\n";
        file.close();
    }
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
    QJsonDocument doc = QJsonDocument::fromJson(replyStr.toUtf8());                
    if (!doc.isObject()) { emit error(); return; }                                 
    QJsonObject obj = doc.object();
    if (obj["AddMsgCount"].toInt() == 0)
        emit noMsg();
    foreach (const QJsonValue & val, obj["AddMsgList"].toArray()) {
        QJsonObject msg = val.toObject();
        QString fromUserNameStr = msg["FromUserName"].toString();
        QString toUserNameStr = msg["ToUserName"].toString();
        QString createTimeStr = QString::number(msg["CreateTime"].toInt());
        QString content = msg["Content"] .toString();

        // TODO: filter <msg></msg> temporarly
        if (content.indexOf("msg") != -1)
            continue;

        if (!m_map.contains(fromUserNameStr + toUserNameStr + createTimeStr)) {
            m_saveLog(createTimeStr, fromUserNameStr, content);
            emit newMsg(content, fromUserNameStr, toUserNameStr);
        }
        
        if ((fromUserNameStr == m_fromUserName && toUserNameStr == m_toUserName) || 
            (fromUserNameStr == m_toUserName && toUserNameStr == m_fromUserName)) {
            if (!m_map.contains(fromUserNameStr + toUserNameStr + createTimeStr)) {
                emit received(content, fromUserNameStr);
            }
        }

        m_map.insert(fromUserNameStr + toUserNameStr + createTimeStr, 
                     msg["CreateTime"].toInt());
    }
    
    m_syncKey.clear();
    foreach (const QJsonValue & val, 
             obj["SyncKey"].toObject()["List"].toArray()) {
        m_syncKey.append(QString::number(val.toObject()["Key"].toInt()) + "|" + 
                QString::number(val.toObject()["Val"].toInt()));
    }
    emit syncKeyChanged();
}
