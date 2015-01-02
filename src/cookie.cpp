// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <time.h>

#include "cookie.h"
#include "globaldeclarations.h"

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

void Cookie::get(QString redirect_uri) 
{
    QString url = redirect_uri + "&fun=new";
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    HttpGet::get(url);
}

void Cookie::getV2(QString redirect_uri)
{
    QString url = redirect_uri.replace(WX_SERVER_HOST, WX_V2_SERVER_HOST) + "&fun=old";
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
    QString ticketStr = "";
    QString expires = "";
    QString domain = "";
    QString path = "";
    QString webwxuvid = ""; 
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
    QString cookiePath = QWXDIR + "/" + COOKIE_FILENAME;
    QDir qwxDir(QWXDIR);
    if (!qwxDir.exists(cookiePath)) qwxDir.mkdir(QWXDIR);
    QFile file(cookiePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "ERROR: fail to save cookie!";
        return;
    }
    QTextStream out(&file);
    QLocale locale = QLocale(QLocale::C, QLocale::AnyCountry);
    foreach (const QNetworkCookie cookie, HttpGet::cookies()) {
        if (HttpGet::cookies().size() > 1) {
            out << QString(cookie.name()) << "=" << QString(cookie.value()) 
                << "; expires=" << locale.toString(cookie.expirationDate(), 
                   "ddd, dd-MMM-yyyy hh:mm:ss") + " GMT" 
                << "; domain=" << cookie.domain() 
                << "; path=" << cookie.path() << endl;
        }
        
        if (QString(cookie.name()) == "webwxuvid") 
            webwxuvid = QString(cookie.value());

        expires = locale.toString(cookie.expirationDate(), 
                                  "ddd, dd-MMM-yyyy hh:mm:ss") + " GMT";
        domain = cookie.domain();
        path = cookie.path();
        if (cookie.name() == "wxuin") 
            uinStr = QString(cookie.value());
        else if (cookie.name() == "wxsid") 
            sidStr = QString(cookie.value());
        else if (cookie.name() == "webwx_data_ticket") 
            ticketStr = QString(cookie.value());
    }
    // TODO: so if webwx V1 fail to get uin and sid, switch to V2
    if (uinStr == "" || sidStr == "" || ticketStr == "") {
        QString href = "window.location.href=";
        int index = replyStr.indexOf(href);
        if (index == -1) {
            qWarning() << "V2 still use XML format for cookie?";
            return;
        } else {
            emit switchToV2();
        }
    } else 
        emit infoChanged(uinStr, sidStr, ticketStr);
    file.close();
}
