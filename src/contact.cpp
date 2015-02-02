// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#if QWX_DEBUG                                                                      
#include <QFile>                                                                   
#endif                                                                             
#include <QJsonDocument>                                                           
#include <QJsonObject>                                                             
#include <QJsonArray>
#include <time.h>

#include "contact.h"
#include "globaldeclarations.h"

Contact::Contact(QObject* parent) 
  : QAbstractListModel(parent)
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

void Contact::addContact(const ContactObject & contact) 
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_contactList << contact;
    endInsertRows();
}

void Contact::post() 
{
    m_clear();

    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxgetcontact?r=" + 
        QString::number(time(NULL));
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{}";
    connect(&m_httpPost, &HttpPost::signalFinished, this, &Contact::m_slotFinished);
    m_httpPost.post(url, json, true);
}

void Contact::postV2() 
{
    m_clear();
    
    QString url = WX_V2_SERVER_HOST + WX_CGI_PATH + "webwxgetcontact?r=" + 
        QString::number(time(NULL));
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString json = "{}";
    connect(&m_httpPost, &HttpPost::signalFinished, this, &Contact::m_slotFinished);
    m_httpPost.post(url, json, true);
}

int Contact::rowCount(const QModelIndex & parent) const 
{
    Q_UNUSED(parent);
    return m_contactList.size();
}

QVariant Contact::data(const QModelIndex & index, int role) const 
{
    if (index.row() < 0 || index.row() >= m_contactList.size())
        return QVariant();

    const ContactObject & contact = m_contactList[index.row()];
    if (role == UserNameRole)
        return contact.userName();
    else if (role == NickNameRole)
        return contact.nickName();
    else if (role == HeadImgUrlRole)
        return contact.headImgUrl();
    return QVariant(); 
}
                                                                                
QHash<int, QByteArray> Contact::roleNames() const 
{
    QHash<int, QByteArray> roles;
    roles[UserNameRole] = "contactUserName";
    roles[NickNameRole] = "nickName";
    roles[HeadImgUrlRole] = "headImgUrl";
    return roles;
}

void Contact::m_clear() 
{
    m_contactList.clear();
}

void Contact::m_slotFinished(QNetworkReply* reply) 
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
        addContact(ContactObject(user["UserName"].toString(), 
                   user["NickName"].toString(), 
                   WX_SERVER_HOST + user["HeadImgUrl"].toString()));
    }                                                                              
    emit contactListChanged();
}

QString Contact::getNickName(QString userName) 
{
    for (int i = 0; i < m_contactList.size(); i++) {
        if (m_contactList[i].userName() == userName)
            return m_contactList[i].nickName();
    }

    return "";
}
