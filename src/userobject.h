// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef USER_OBJECT_H
#define USER_OBJECT_H

#include <QObject>
#include <QString>

class UserObject : public QObject 
{
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString nickName READ nickName WRITE setNickName NOTIFY nickNameChanged)
    Q_PROPERTY(QString headImgUrl READ headImgUrl WRITE setHeadImgUrl NOTIFY headImgUrlChanged)

public:
    UserObject(const QString userName, 
               const QString nickName, 
               const QString headImgUrl, 
               QObject* parent = nullptr) 
      : QObject(parent) 
    {
        m_userName = userName; m_nickName = nickName; m_headImgUrl = headImgUrl;
    }

    QString userName() const { return m_userName; }
    void setUserName(const QString & userName) 
    { m_userName = userName; emit userNameChanged(); }

    QString nickName() const { return m_nickName; }
    void setNickName(const QString & nickName) 
    { m_nickName = nickName; emit nickNameChanged(); }

    QString headImgUrl() const { return m_headImgUrl; }
    void setHeadImgUrl(const QString & headImgUrl) 
    { m_headImgUrl = headImgUrl; emit headImgUrlChanged(); }

Q_SIGNALS:
    void userNameChanged();
    void nickNameChanged();
    void headImgUrlChanged();

private:
    QString m_userName;
    QString m_nickName;
    QString m_headImgUrl;
};

#endif // USER_OBJECT_H
