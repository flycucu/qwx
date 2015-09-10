// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QJsonDocument>                                                           
#include <QJsonObject>

#include "ipcity.h"
#include "globaldeclarations.h"

IpCity::IpCity(HttpGet* parent) 
  : HttpGet(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

IpCity::~IpCity() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void IpCity::get() { HttpGet::get(IPLOOKUP_URL); }

void IpCity::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(replyStr.toUtf8());
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << replyStr;
#endif
    if (!doc.isObject()) return;
    QJsonObject obj = doc.object();
    QString city = obj["city"].toString();
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << city;
#endif
    emit cityChanged(city);
}
