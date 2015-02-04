// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef SYNC_H
#define SYNC_H

#include "httppost.h"

class Sync : public HttpPost 
{
    Q_OBJECT

    Q_PROPERTY(QStringList syncKey READ syncKey NOTIFY syncKeyChanged)

public:
    Sync(HttpPost* parent = nullptr);
    ~Sync();

    QStringList syncKey() const { return m_syncKey; }

    Q_INVOKABLE void post(QString uin, 
                          QString sid, 
                          QString skey, 
                          QStringList syncKey);
    Q_INVOKABLE void postV2(QString uin, 
                            QString sid, 
                            QString skey, 
                            QStringList syncKey);

Q_SIGNALS:
    void error();
    void syncKeyChanged();

protected:
    void finished(QNetworkReply* reply);

private:
    void m_post(QString host, 
                QString uin, 
                QString sid, 
                QString skey, 
                QStringList syncKey);

private:
    QStringList m_syncKey;
};

#endif // SYNC_H
