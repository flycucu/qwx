// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef MOD_CONTACT_H
#define MOD_CONTACT_H

#include "httppost.h"

class ModContact : public HttpPost 
{
    Q_OBJECT

    Q_PROPERTY(QString uin READ uin WRITE setUin NOTIFY uinChanged)
    Q_PROPERTY(QString sid READ sid WRITE setSid NOTIFY sidChanged)
    Q_PROPERTY(QList<QObject*> modContactList READ modContactList NOTIFY modContactListChanged)

public:
    ModContact(HttpPost* parent = nullptr);
    ~ModContact();

    QString uin() const;
    void setUin(const QString & uin);

    QString sid() const;
    void setSid(const QString & sid);

    QList<QObject*> modContactList() const;

Q_SIGNALS:
    void error();
    void uinChanged();
    void sidChanged();
    void modContactListChanged();

protected:
    void finished(QNetworkReply* reply);

private:
    QString m_uin;
    QString m_sid;
    QList<QObject*> m_modContactList;

private:
    void m_clear();
    void m_post();
};

#endif // MOD_CONTACT_H
