// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QDomDocument>
#include <QDomElement>

#include "cookie.h"

Cookie::Cookie(HttpGet* parent) 
  : HttpGet(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

Cookie::~Cookie() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

QVariant Cookie::cookies() const 
{
    QVariant var;
    var.setValue(HttpGet::cookies());
    return var;
}

void Cookie::get(QString redirect_uri) 
{
    QString url = redirect_uri + "&fun=new";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url);
}

void Cookie::finished(QNetworkReply* reply) 
{
    QString replyStr(reply->readAll());
    QString uinStr = "";
    QString sidStr = "";
    QDomDocument doc;

#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
    foreach (const QNetworkCookie cookie, HttpGet::cookies()) {
        if (cookie.name() == "wxuin") 
            uinStr = QString(cookie.value());
        else if (cookie.name() == "wxsid") 
            sidStr = QString(cookie.value());
    }
    
    emit infoChanged(uinStr, sidStr);
}

