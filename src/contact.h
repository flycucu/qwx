// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef CONTACT_H
#define CONTACT_H

#include <QAbstractListModel>

#include "httppost.h"
#include "userobject.h"

class Contact : public QAbstractListModel 
{
    Q_OBJECT

public:
    enum ContactRoles {
        UserNameRole = Qt::UserRole + 1,
        NickNameRole,
        HeadImgUrlRole
    };

    explicit Contact(QObject* parent = nullptr);
    ~Contact();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    
    Q_INVOKABLE void addContact(QString userName, QString nickName, QString headImgUrl);
    Q_INVOKABLE void post();
    Q_INVOKABLE void postV2();
    Q_INVOKABLE QString getNickName(QString nickName);

Q_SIGNALS:
    void error();
    void contactListChanged();

protected:
    QHash<int, QByteArray> roleNames() const;

private Q_SLOTS:
    void m_slotFinished(QNetworkReply* reply);

private:
    QList<UserObject*> m_contactList;
    HttpPost m_httpPost;
};

#endif // CONTACT_H
