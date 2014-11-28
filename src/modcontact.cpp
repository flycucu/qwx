// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#if QWX_DEBUG
#include <QFile>
#endif
#include <QJsonDocument>                                                           
#include <QJsonObject>                                                             
#include <QJsonArray>

#include "modcontact.h"
#include "userobject.h"
#include "globaldeclarations.h"

ModContact::ModContact(HttpPost* parent) 
  : HttpPost(parent), 
    m_uin(""), 
    m_sid("") 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

ModContact::~ModContact() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
    m_clear();
}

QString ModContact::uin() const { return m_uin; }
void ModContact::setUin(const QString & uin) 
{
    if (m_uin == uin) return;
    m_uin = uin; emit uinChanged();
}

QString ModContact::sid() const { return m_sid; }
void ModContact::setSid(const QString & sid) 
{
    if (m_sid == sid) return;
    m_sid = sid;
    if (m_uin != "") {
        emit sidChanged(); 
        m_post();
    }
}

void ModContact::m_clear() 
{
    foreach (QObject* obj, m_modContactList) {
        if (obj) delete obj; obj = nullptr;
    }
    m_modContactList.clear();
}

void ModContact::m_post() 
{
    QString ts = QString::number(time(NULL));
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxsync?sid=" + m_sid 
        + "&r=" + ts;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{\"BaseRequest\":{\"Uin\":" + m_uin 
        + ",\"Sid\":\"" + m_sid + 
        "\"},\"SyncKey\":{\"Count\":4,\"List\":[{\"Key\":1,\"Val\":620916854},"
        "{\"Key\":2,\"Val\":620917961},{\"Key\":3,\"Val\":620917948},"
        "{\"Key\":1000,\"Val\":1388967977}]},\"rr\":" + ts + "}";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << json;
#endif
    HttpPost::post(url, json);
}

QList<QObject*> ModContact::modContactList() const { return m_modContactList; }

void ModContact::finished(QNetworkReply* reply) 
{
    m_modContactList.clear();
    QString replyStr = QString(reply->readAll());
#if QWX_DEBUG
    QFile file("modcontact.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << replyStr;
        file.close();
    }
#endif
    QJsonDocument doc = QJsonDocument::fromJson(replyStr.toUtf8());
    if (!doc.isObject()) { emit error(); return; }
    QJsonObject obj = doc.object();
    QJsonArray arr = obj["ModContactList"].toArray();
    foreach (const QJsonValue & val, arr) {
        QJsonObject user = val.toObject();
        m_modContactList.append(new UserObject(
            user["UserName"].toString(), 
            user["NickName"].toString(), 
            WX_SERVER_HOST + user["HeadImgUrl"].toString()));
    }
    emit modContactListChanged();
}
