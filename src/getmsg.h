// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef GET_MSG_H
#define GET_MSG_H

#include "httppost.h"

class GetMsg : public HttpPost 
{
    Q_OBJECT

    Q_PROPERTY(QString fromUserName READ fromUserName WRITE setFromUserName NOTIFY fromUserNameChanged)

public:
    GetMsg(HttpPost* parent = nullptr);
    ~GetMsg();

    QString fromUserName() const;
    void setFromUserName(const QString & fromUserName);

    Q_INVOKABLE void post(QString uin, QString sid, QStringList syncKey);

Q_SIGNALS:
    void fromUserNameChanged();
    void error();
    void received(QString content);

protected:
    void finished(QNetworkReply* reply);

private:
    QString m_fromUserName;
};

#endif // GET_MSG_H
