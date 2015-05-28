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
    m_toUserName(""),
    m_needSaveLog(true)
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

void GetMsg::setFromUserName(const QString & fromUserName) 
{
    if (m_fromUserName != fromUserName) {
        m_fromUserName = fromUserName;
        emit fromUserNameChanged();
    }
}

void GetMsg::setToUserName(const QString & toUserName) 
{
    if (m_toUserName != toUserName) {
        m_toUserName = toUserName;
        emit toUserNameChanged();
    }
}

void GetMsg::setNeedSaveLog(bool needSaveLog) 
{
    if (m_needSaveLog != needSaveLog) {
        m_needSaveLog = needSaveLog;
        emit needSaveLogChanged();
    }
}

void GetMsg::m_post(QString host, 
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

void GetMsg::post(QString uin, QString sid, QString skey, QStringList syncKey) 
{
    m_post(WX_SERVER_HOST, uin, sid, skey, syncKey);
}

void GetMsg::postV2(QString uin, QString sid, QString skey, QStringList syncKey)
{
    m_post(WX_V2_SERVER_HOST, uin, sid, skey, syncKey);
}

QString GetMsg::contentWithoutUserName(QString content) 
{
    if (content.startsWith("@"))
        return content.mid(content.indexOf(":<br/>") + QString(":<br/>").size());

    return content;
}

QString GetMsg::contentToUserName(QString content, QString oriUserName) 
{
    if (content.startsWith("@")) 
        return content.left(content.indexOf(":<br/>"));

    return oriUserName;
}

void GetMsg::m_saveLog(QString createTimeStr, QString fromUserName, QString content) 
{
    QFile file(QWXDIR + "/" + fromUserName + ".txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << createTimeStr << DELIM << fromUserName << DELIM << content << "\n";
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
        emit noNewMsg();

    foreach (const QJsonValue & val, obj["AddMsgList"].toArray()) {
        QJsonObject msg = val.toObject();
        QString fromUserNameStr = msg["FromUserName"].toString();
        QString toUserNameStr = msg["ToUserName"].toString();
        QString createTimeStr = QString::number(msg["CreateTime"].toInt());
        QString content = msg["Content"] .toString();
        
        if (!m_map.contains(fromUserNameStr + toUserNameStr + createTimeStr)) {
            if (m_needSaveLog)
                m_saveLog(createTimeStr, fromUserNameStr, content);

            emit newMsg(content, fromUserNameStr, toUserNameStr);
        }
        
        if ((fromUserNameStr == m_fromUserName && toUserNameStr == m_toUserName) || 
            (fromUserNameStr == m_toUserName && toUserNameStr == m_fromUserName)) {
            if (!m_map.contains(fromUserNameStr + toUserNameStr + createTimeStr)) {
                emit received(content, fromUserNameStr);
            }
        }

        if (m_map.size() > 64) {
            while (m_map.size() > 64 / 2)
                m_map.erase(m_map.begin());
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
