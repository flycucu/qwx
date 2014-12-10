// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QJsonDocument>                                                           
#include <QJsonObject>

#include "rmbz.h"
#include "globaldeclarations.h"

Rmbz::Rmbz(HttpGet* parent) 
  : HttpGet(parent)
{
#if QIRI_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

Rmbz::~Rmbz() 
{
#if QIRI_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void Rmbz::get(QString word) 
{ 
    QString url = RMBZ_URL + word;
#if QIRI_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url); 
}

void Rmbz::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(replyStr.toUtf8());
#if QIRI_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << replyStr;
#endif
    if (!doc.isObject()) return;
    QJsonObject obj = doc.object();
    emit contentChanged(obj["content"].toString());
}
