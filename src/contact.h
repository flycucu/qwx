// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef CONTACT_H
#define CONTACT_H

#include <QAbstractListModel>

#include "httppost.h"

class ContactObject;

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
    
    Q_INVOKABLE void addContact(const ContactObject & contact);
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
    void m_clear();
    void m_post(QString host);

private:
    QList<ContactObject> m_contactList;
    HttpPost m_httpPost;
};

class ContactObject 
{
public:
    ContactObject(const QString & userName, 
                  const QString & nickName, 
                  const QString & headImgUrl) 
      : m_userName(userName), m_nickName(nickName), m_headImgUrl(headImgUrl)
    {
    }

    QString userName() const { return m_userName; }
    QString nickName() const { return m_nickName; }
    QString headImgUrl() const { return m_headImgUrl; }

private:
    QString m_userName;
    QString m_nickName;
    QString m_headImgUrl;
};

#endif // CONTACT_H
