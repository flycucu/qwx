// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef CONTACT_H
#define CONTACT_H

#include "httppost.h"

class Contact : public HttpPost 
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> contactList READ contactList NOTIFY contactListChanged)

public:
    Contact(HttpPost* parent = nullptr);
    ~Contact();

    QList<QObject*> contactList() const;

    Q_INVOKABLE void post();
    Q_INVOKABLE void postV2();

Q_SIGNALS:
    void error();
    void contactListChanged();

protected:
    void finished(QNetworkReply* reply);

private:
    QList<QObject*> m_contactList;
};

#endif // CONTACT_H
