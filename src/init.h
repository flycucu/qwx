// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef INIT_H
#define INIT_H

#include "httppost.h"

class Init : public HttpPost 
{
    Q_OBJECT

    
    Q_PROPERTY(QString deviceId READ deviceId NOTIFY deviceIdChanged)
    Q_PROPERTY(QString loginUserName READ loginUserName NOTIFY loginUserNameChanged)
    Q_PROPERTY(QString loginNickName READ loginNickName NOTIFY loginNickNameChanged)
    Q_PROPERTY(QList<QObject*> contactList READ contactList NOTIFY contactListChanged)
    Q_PROPERTY(QString loginHeadImgUrl READ loginHeadImgUrl NOTIFY loginHeadImgUrlChanged)

public:
    Init(HttpPost* parent = nullptr);
    ~Init();

    QString deviceId() const { return m_deviceId; }
    QString loginUserName() const { return m_loginUserName; }
    QString loginNickName() const { return m_loginNickName; }
    QList<QObject*> contactList() const { return m_contactList; }
    QString loginHeadImgUrl() const;

    Q_INVOKABLE void post(QString uin, QString sid, QString ticket);
    Q_INVOKABLE void postV2(QString uin, QString sid, QString ticket);

Q_SIGNALS:
    void error();
    void skeyChanged(QString skey, QStringList syncKey);
    void deviceIdChanged();
    void loginUserNameChanged();
    void loginNickNameChanged();
    void contactListChanged();
    void loginHeadImgUrlChanged();

protected:
    void finished(QNetworkReply* reply);

private:
    bool m_v2;
    QString m_deviceId;
    QString m_loginUserName;
    QString m_loginNickName;
    QList<QObject*> m_contactList;
    QMap<QString, QString> m_map;

private:
    void m_clear();
};

#endif // INIT_H
