// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QJsonDocument>                                                           
#include <QJsonObject>
#include <QJsonArray>

#include "weather.h"
#include "globaldeclarations.h"

const QString REALTIME_TEMP = "实时：";

Weather::Weather(HttpGet* parent) 
  : HttpGet(parent), 
    m_city("")
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

Weather::~Weather() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void Weather::get(QString city) 
{
    m_city = city;
    QString url = QString(WEATHER_URL).arg(m_city);
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url); 
}

void Weather::finished(QNetworkReply* reply) 
{
    QString replyStr = QString(reply->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(replyStr.toUtf8());
    QString pm25Str = "";
    QString curTempStr = "";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << replyStr;
#endif
    if (!doc.isObject()) return;
    QJsonObject root = doc.object();
    QJsonObject result = root["results"].toArray().at(0).toObject();
    pm25Str = result["pm25"].toString();
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << pm25Str;
#endif
    QJsonObject weather = result["weather_data"].toArray().at(0).toObject();
    QString weatherDate = weather["date"].toString();
    if (weatherDate.contains(REALTIME_TEMP)) {
        int index = weatherDate.indexOf(REALTIME_TEMP);
        curTempStr = weatherDate.mid(index, weatherDate.size() - index - 1);
    }
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << curTempStr;
#endif
    emit weatherChanged(m_city + "，PM 2.5：" + pm25Str + "，" + curTempStr + 
            "，" + weather["weather"].toString() + "，" + 
            weather["wind"].toString() + "，" + weather["temperature"].toString());
}
