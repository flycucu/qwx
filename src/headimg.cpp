// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QDir>

#include "headimg.h"
#include "globaldeclarations.h"

HeadImg::HeadImg(QObject* parent) 
  : QObject(parent), 
    m_v2(false),
    m_userName(""), 
    m_headImgUrl(""),
    m_filePath("")
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

HeadImg::~HeadImg() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void HeadImg::setV2(bool v2)
{
    if (m_v2 != v2) {
        m_v2 = v2;
        emit v2Changed();
    }
}

void HeadImg::setUserName(const QString & userName) 
{
    m_userName = userName;
    emit userNameChanged();
    m_v2 ? m_get(WX_V2_SERVER_HOST) : m_get(WX_SERVER_HOST);
}

void HeadImg::setHeadImgUrl(const QString & headImgUrl) 
{
    m_headImgUrl = headImgUrl;
    emit headImgUrlChanged();
    m_v2 ? m_get(WX_V2_SERVER_HOST) : m_get(WX_SERVER_HOST);
}

void HeadImg::m_get(QString host) 
{
    QString url = host + (m_headImgUrl.contains("webwxgeticon") ? 
        WX_CGI_PATH + "webwxgeticon?seq=1388335457&username=" + m_userName : 
        WX_CGI_PATH + "webwxgetheadimg??seq=1388335457&username=" + m_userName);
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString headImgPath = QWXDIR + "/" + m_userName;
    if (QFile::exists(headImgPath)) { 
        m_filePath = "file://" + QWXDIR + "/" + m_userName;
        emit filePathChanged();
    } else {
        m_downLoad.get(url, headImgPath);
        m_connection = connect(&m_downLoad, &Download::finished, [this] {
                    disconnect(m_connection);
                    m_filePath = "file://" + QWXDIR + "/" + m_userName;
                    emit filePathChanged();
                });
    }
}
