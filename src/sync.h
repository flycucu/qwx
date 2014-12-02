// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

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

    QStringList syncKey() const;

    Q_INVOKABLE void post(QString uin, QString sid, QStringList syncKey);

Q_SIGNALS:
    void error();
    void syncKeyChanged();

protected:
    void finished(QNetworkReply* reply);

private:
    QStringList m_syncKey;
};

#endif // SYNC_H
