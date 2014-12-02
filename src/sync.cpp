// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#if QWX_DEBUG
#include <QFile>
#endif
#include <QJsonDocument>                                                           
#include <QJsonObject>                                                             
#include <QJsonArray>

#include "sync.h"
#include "globaldeclarations.h"

Sync::Sync(HttpPost* parent) 
  : HttpPost(parent) 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

Sync::~Sync() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

QStringList Sync::syncKey() const { return m_syncKey; }

void Sync::post(QString uin, QString sid, QStringList syncKey) 
{
    if (syncKey.size() != 4) { emit error(); return; }
    
    QString ts = QString::number(time(NULL));
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxsync?sid=" + sid + 
        "&r=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":" + uin + ",\"Sid\":\"" + sid + 
        "\"},\"SyncKey\":{\"Count\":4,\"List\":[{\"Key\":1,\"Val\":" + 
        syncKey[0] + "},{\"Key\":2,\"Val\":" + syncKey[1] + 
        "},{\"Key\":3,\"Val\":" + syncKey[2] + "},{\"Key\":1000,\"Val\":" + 
        syncKey[3] + "}]},\"rr\":" + ts + "}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json, true);
}

void Sync::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
    QFile file("sync.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << replyStr;
        file.close();
    }
#endif
    QJsonDocument doc = QJsonDocument::fromJson(replyStr.toUtf8());                
    if (!doc.isObject()) { emit error(); return; }                                 
    QJsonObject obj = doc.object();
    foreach (const QJsonValue & val, obj["SyncKey"].toObject()["List"].toArray()) {
        m_syncKey.append(QString::number(val.toObject()["Val"].toInt()));            
    }                                                                              
    emit syncKeyChanged();
}
