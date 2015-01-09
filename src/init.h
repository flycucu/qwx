// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef INIT_H
#define INIT_H

#include "httppost.h"

class Init : public HttpPost 
{
    Q_OBJECT

    
    Q_PROPERTY(QString deviceId NOTIFY deviceIdChanged)
    Q_PROPERTY(QString loginUserName READ loginUserName NOTIFY loginUserNameChanged)
    Q_PROPERTY(QList<QObject*> contactList READ contactList NOTIFY contactListChanged)
    Q_PROPERTY(QString loginHeadImgUrl READ loginHeadImgUrl NOTIFY loginHeadImgUrlChanged)

public:
    Init(HttpPost* parent = nullptr);
    ~Init();

    QString deviceId() const;

    QString loginUserName() const;

    QList<QObject*> contactList() const;

    QString loginHeadImgUrl() const;

    Q_INVOKABLE void post(QString uin, QString sid, QString ticket);
    Q_INVOKABLE void postV2(QString uin, QString sid, QString ticket);

Q_SIGNALS:
    void error();
    void skeyChanged(QString skey, QStringList syncKey);
    void deviceIdChanged();
    void loginUserNameChanged();
    void contactListChanged();
    void loginHeadImgUrlChanged();

protected:
    void finished(QNetworkReply* reply);

private:
    bool m_v2;
    QString m_deviceId;
    QString m_loginUserName;
    QList<QObject*> m_contactList;
    QMap<QString, QString> m_map;

private:
    void m_clear();
};

#endif // INIT_H
