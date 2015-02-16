// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef CONTACT_H
#define CONTACT_H

#include "httppost.h"
#include "userobject.h"

class Contact : public QObject 
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> contactList READ contactList NOTIFY contactListChanged)

public:
    explicit Contact(QObject* parent = nullptr);
    ~Contact();

    QList<QObject*> contactList() const { return m_contactList; }

    Q_INVOKABLE void post();
    Q_INVOKABLE void postV2();
    Q_INVOKABLE QString getNickName(QString userName);
    Q_INVOKABLE QString getHeadImgUrl(QString userName);

Q_SIGNALS:
    void error();
    void contactListChanged();

private Q_SLOTS:
    void m_slotFinished(QNetworkReply* reply);

private:
    void m_clear();
    void m_post(QString host);

private:
    HttpPost m_httpPost;
    QList<QObject*> m_contactList;
    bool m_v2;
};

#endif // CONTACT_H
