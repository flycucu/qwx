// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QDir>
#include <QDomDocument>
#include <QDomElement>

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
    QString expires = "";
    QString domain = "";
    QString path = "";
    QString webwxuvid = ""; 
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
    qDebug() << "DEBUG:" << replyStr;
#endif
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
        if (QString(cookie.name()) == "webwxuvid") 
            webwxuvid = QString(cookie.value());

        expires = locale.toString(cookie.expirationDate(), 
                                  "ddd, dd-MMM-yyyy hh:mm:ss") + " GMT";
        domain = cookie.domain();
        path = cookie.path();
        // FIXME: webwx removed wxuin and wxsid from cookie!
        if (cookie.name() == "wxuin") 
            uinStr = QString(cookie.value());
        else if (cookie.name() == "wxsid") 
            sidStr = QString(cookie.value());
    }
    // FIXME: so I even do not need to check whether or not uin or sid is empty
    QDomDocument doc;
    if (doc.setContent(replyStr) == false) {
        qWarning() << "ERROR:" << __PRETTY_FUNCTION__ << "fail to parse";
        return;
    }
    QDomElement root = doc.documentElement();
    QDomElement skey = root.firstChildElement("skey");
    QDomElement sid = root.firstChildElement("wxsid");
    QDomElement uin = root.firstChildElement("wxuin");
    QDomElement ticket = root.firstChildElement("pass_ticket");
    uinStr = uin.text();
    sidStr = sid.text();
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << uinStr << sidStr;
#endif
    // FIXME: so I have to save cookie name/value by myself
    out << "wxuin=" << uinStr << "; expires=" << expires << "; domain=" 
        << domain << "; path=" << path << endl;
    out << "wxsid=" << sidStr << "; expires=" << expires << "; domain="            
        << domain << "; path=" << path << endl;
    out << "wxloadtime=" << QString::number(time(NULL)) << "; expires=" 
        << expires << "; domain=" << domain << "; path=" << path << endl;
    out << "mm_lang=zh_CN; expires=" << expires << "; domain=" << domain 
        << "; path=" << path << endl;
    out << "webwx_data_ticket=" << ticket.text() << "; expires=" << expires 
        << "; domain=" << domain << "; path=" << path << endl;
    out << "webwxuvid=" << webwxuvid << "; expires=" << expires << "; domain="            
        << domain << "; path=" << path << endl;
    file.close();
    emit infoChanged(uinStr, sidStr, skey.text(), ticket.text());
}
