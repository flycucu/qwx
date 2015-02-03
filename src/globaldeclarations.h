// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef GLOBAL_DECLARATIONS_H
#define GLOBAL_DECLARATIONS_H

#include <QString>
#include <QDir>

const QString CODE_NAME = "qwx";
const QString APPLICATION_VERSION = "0.1.1";
const QString APPLICATION_ENCODING = "UTF-8";
const QString LOGIN_SERVER_HOST = "https://login.weixin.qq.com";
const QString WX_SERVER_HOST = "https://wx.qq.com";
const QString WX_V2_SERVER_HOST = "https://wx2.qq.com";
const QString WX_CGI_PATH = "/cgi-bin/mmwebwx-bin/";
const QString XIAODOUBI_URL = "http://www.xiaodoubi.com/bot/api.php?chat=";
const QString QWXDIR = QDir::homePath() + "/." + CODE_NAME;
const QString COOKIE_FILENAME = ".cookie";
const QString DELIM = ";|";

#endif // GLOBAL_DECLARATIONS_H
