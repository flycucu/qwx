// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#if QWX_DEBUG                                                                      
#include <QFile>                                                                   
#endif                                                                             
#include <QJsonDocument>                                                           
#include <QJsonObject>                                                             
#include <QJsonArray>
#include <time.h>

#include "contact.h"
#include "userobject.h"
#include "globaldeclarations.h"

Contact::Contact(HttpPost* parent) 
  : HttpPost(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

Contact::~Contact() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

QList<QObject*> Contact::contactList() const { return m_contactList; }

void Contact::post() 
{
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxgetcontact?r=" + 
        QString::number(time(NULL));
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{}";
    HttpPost::post(url, json, true);
}

void Contact::postV2() 
{
    QString url = WX_V2_SERVER_HOST + WX_CGI_PATH + "webwxgetcontact?r=" + 
        QString::number(time(NULL));
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{}";
    HttpPost::post(url, json, true);
}

void Contact::finished(QNetworkReply* reply) 
{
    QString replyStr(reply->readAll());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
    QFile file("contact.json");                                                 
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {                       
        QTextStream out(&file);                                                    
        out << replyStr;                                                           
        file.close();                                                              
    }                                                                              
#endif
    QJsonDocument doc = QJsonDocument::fromJson(replyStr.toUtf8());                
    if (!doc.isObject()) { emit error(); return; }                                 
    QJsonObject obj = doc.object();                                                
    QJsonArray arr = obj["MemberList"].toArray();                              
    foreach (const QJsonValue & val, arr) {                                        
        QJsonObject user = val.toObject();                                         
        m_contactList.append(new UserObject(                                    
            user["UserName"].toString(),                                           
            user["NickName"].toString(),                                           
            WX_SERVER_HOST + user["HeadImgUrl"].toString()));                      
    }                                                                              
    emit contactListChanged();
}
