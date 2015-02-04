// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#if QWX_DEBUG
#include <QFile>
#endif
#include <QJsonDocument>                                                           
#include <QJsonObject>                                                             
#include <QJsonArray>
#include <time.h>

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

void Sync::m_post(QString host, 
                  QString uin, 
                  QString sid, 
                  QString skey, 
                  QStringList syncKey) 
{
    QString ts = QString::number(time(NULL));
    QString url = host + WX_CGI_PATH + "webwxsync?sid=" + sid + "&skey=" + skey + "&r=" + ts;
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

void Sync::post(QString uin, QString sid, QString skey, QStringList syncKey) 
{
    m_post(WX_SERVER_HOST, uin, sid, skey, syncKey);
}

void Sync::postV2(QString uin, QString sid, QString skey, QStringList syncKey)
{
    m_post(WX_V2_SERVER_HOST, uin, sid, skey, syncKey);
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
    m_syncKey.clear();
    foreach (const QJsonValue & val, obj["SyncKey"].toObject()["List"].toArray()) {
        m_syncKey.append(QString::number(val.toObject()["Key"].toInt()) + "|" + 
                QString::number(val.toObject()["Val"].toInt()));
    }                                                                              
    emit syncKeyChanged();
}
