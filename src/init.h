// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef INIT_H
#define INIT_H

#include "httppost.h"

class Init : public HttpPost 
{
    Q_OBJECT

    Q_PROPERTY(QString loginUserName READ loginUserName NOTIFY loginUserNameChanged)
    Q_PROPERTY(QList<QObject*> contactList READ contactList NOTIFY contactListChanged)

public:
    Init(HttpPost* parent = nullptr);
    ~Init();

    QString loginUserName() const;

    QList<QObject*> contactList() const;

    Q_INVOKABLE void post(QString uin, QString sid);

Q_SIGNALS:
    void error();
    void skeyChanged(QString skey);
    void loginUserNameChanged();
    void contactListChanged();

protected:
    void finished(QNetworkReply* reply);

private:
    QString m_loginUserName;
    QList<QObject*> m_contactList;

private:
    void m_clear();
};

#endif // INIT_H
