// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef GET_MSG_H
#define GET_MSG_H

#include <QMap>

#include "httppost.h"

class GetMsg : public HttpPost 
{
    Q_OBJECT

    Q_PROPERTY(QString fromUserName READ fromUserName WRITE setFromUserName NOTIFY fromUserNameChanged)
    Q_PROPERTY(QString toUserName READ toUserName WRITE setToUserName NOTIFY toUserNameChanged)

public:
    GetMsg(HttpPost* parent = nullptr);
    ~GetMsg();

    QString fromUserName() const;
    void setFromUserName(const QString & fromUserName);

    QString toUserName() const;
    void setToUserName(const QString & toUserName);

    Q_INVOKABLE void post(QString uin, QString sid, QStringList syncKey);

Q_SIGNALS:
    void fromUserNameChanged();
    void toUserNameChanged();
    void error();
    void received(QString content, QString userName);

protected:
    void finished(QNetworkReply* reply);

private:
    QString m_fromUserName;
    QString m_toUserName;
    QMap<QString, int> m_map;
};

#endif // GET_MSG_H
