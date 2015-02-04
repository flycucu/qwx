// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef STAT_REPORT_H
#define STAT_REPORT_H

#include "httppost.h"

class StatReport : public HttpPost 
{
    Q_OBJECT

public:
    StatReport(HttpPost* parent = nullptr);
    ~StatReport();

    Q_INVOKABLE void firstRequestSuccess(QString uuid);
    Q_INVOKABLE void secondRequestStart(QString uuid);
    Q_INVOKABLE void post(QString uuid);
    Q_INVOKABLE void postV2(QString uuid);

protected:
    void finished(QNetworkReply* reply);

private:
    void m_post(QString host, QString uuid);
};

#endif // STAT_REPORT_H
