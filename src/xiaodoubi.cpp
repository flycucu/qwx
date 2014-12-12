// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QJsonDocument>                                                           
#include <QJsonObject>

#include "xiaodoubi.h"
#include "globaldeclarations.h"

XiaoDouBi::XiaoDouBi(HttpGet* parent) 
  : HttpGet(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

XiaoDouBi::~XiaoDouBi() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void XiaoDouBi::get(QString word) 
{ 
    QString idiomStr = m_idiom.get(word);
    if (idiomStr != "") { emit contentChanged(idiomStr); return; }
    QString url = XIAODOUBI_URL + word;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url); 
}

void XiaoDouBi::finished(QNetworkReply* reply) 
{
    emit contentChanged(QString(reply->readAll()));
}
