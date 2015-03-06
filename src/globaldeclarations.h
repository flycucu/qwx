// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef GLOBAL_DECLARATIONS_H
#define GLOBAL_DECLARATIONS_H

#include <QString>
#include <QDir>

const QString CODE_NAME = "qwx";
const QString APPLICATION_VERSION = "0.2";
const QString APPLICATION_ENCODING = "UTF-8";
const QString TRANSLATIONS_PATH = "translations";

const QString LOGIN_SERVER_HOST = "https://login.weixin.qq.com";
const QString WX_SERVER_HOST = "https://wx.qq.com";
const QString WX_V2_SERVER_HOST = "https://wx2.qq.com";
const QString WX_CGI_PATH = "/cgi-bin/mmwebwx-bin/";
const QString XIAODOUBI_URL = "http://www.xiaodoubi.com/bot/api.php?chat=";
const QString QWXDIR = QDir::homePath() + "/." + CODE_NAME;
const QString COOKIE_FILENAME = ".cookie";
const QString DELIM = ";|";

const QString IPLOOKUP_URL = "http://int.dpool.sina.com.cn/iplookup/iplookup.php?format=json";
const QString WEATHER_URL = "http://api.map.baidu.com/telematics/v3/weather?location=%1&output=json&ak=6xxzcQMhb4WgKX0EUkwG747K";

#endif // GLOBAL_DECLARATIONS_H
