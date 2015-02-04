// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef GET_MSG_H
#define GET_MSG_H

#include "httppost.h"

class GetMsg : public HttpPost 
{
    Q_OBJECT

    Q_PROPERTY(QString fromUserName READ fromUserName WRITE setFromUserName NOTIFY fromUserNameChanged)
    Q_PROPERTY(QString toUserName READ toUserName WRITE setToUserName NOTIFY toUserNameChanged)
    Q_PROPERTY(QStringList syncKey READ syncKey NOTIFY syncKeyChanged)
    Q_PROPERTY(bool needSaveLog READ needSaveLog WRITE setNeedSaveLog NOTIFY needSaveLogChanged)

public:
    GetMsg(HttpPost* parent = nullptr);
    ~GetMsg();

    QString fromUserName() const { return m_fromUserName; }
    void setFromUserName(const QString & fromUserName);

    QString toUserName() const { return m_toUserName; }
    void setToUserName(const QString & toUserName);
    
    QStringList syncKey() const { return m_syncKey; }

    bool needSaveLog() const { return m_needSaveLog; }
    void setNeedSaveLog(bool needSaveLog);

    Q_INVOKABLE void post(QString uin, 
                          QString sid, 
                          QString skey, 
                          QStringList syncKey);
    Q_INVOKABLE void postV2(QString uin, 
                            QString sid, 
                            QString skey, 
                            QStringList syncKey);

Q_SIGNALS:
    void fromUserNameChanged();
    void toUserNameChanged();
    void error();
    void received(QString content, QString userName);
    void newMsg(QString content, QString fromUserName, QString toUserName);
    void syncKeyChanged();
    void noMsg();
    void needSaveLogChanged();

protected:
    void finished(QNetworkReply* reply);

private:
    void m_saveLog(QString createTimeStr, QString fromUserName, QString content);
    void m_post(QString host, 
                QString uin, 
                QString sid, 
                QString skey, 
                QStringList syncKey);

private:
    QString m_fromUserName;
    QString m_toUserName;
    QMap<QString, int> m_map;
    QStringList m_syncKey;
    bool m_needSaveLog;
};

#endif // GET_MSG_H
