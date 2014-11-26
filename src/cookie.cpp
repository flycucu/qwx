// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QDir>

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

void Cookie::finished(QNetworkReply* reply) 
{
    QString replyStr(reply->readAll());
    QString uinStr = "";
    QString sidStr = "";

#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
    //-------------------------------------------------------------------------
    // TODO: save cookies
    QString cookiePath = QWXDIR + "/cookies";
    QDir qwxDir(QWXDIR);
    if (!qwxDir.exists(cookiePath)) qwxDir.mkdir(QWXDIR);
    QFile file(cookiePath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qWarning() << "ERROR: fail to save cookies!";
        return;
    }
    QTextStream out(&file);
    QLocale locale = QLocale(QLocale::C, QLocale::AnyCountry);
    foreach (const QNetworkCookie cookie, HttpGet::cookies()) {
        out << QString(cookie.name()) << "=" << QString(cookie.value()) 
            << "; expires=" << locale.toString(cookie.expirationDate(), "ddd, dd-MMM-yyyy hh:mm:ss") + " GMT" 
            << "; domain=" << cookie.domain() 
            << "; path=" << cookie.path() << endl;

        if (cookie.name() == "wxuin") 
            uinStr = QString(cookie.value());
        else if (cookie.name() == "wxsid") 
            sidStr = QString(cookie.value());
    }
    file.close();
    //-------------------------------------------------------------------------
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << uinStr << sidStr;
#endif
    emit infoChanged(uinStr, sidStr);
}
