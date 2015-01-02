// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QDir>

#include "headimg.h"
#include "globaldeclarations.h"

HeadImg::HeadImg(QObject* parent) 
  : QObject(parent), 
    m_v2(false),
    m_userName(""), 
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

bool HeadImg::v2() const { return m_v2; }
void HeadImg::setV2(bool v2)
{
    if (m_v2 == v2)
        return;
    m_v2 = v2;
    emit v2Changed();
    emit m_getV2();
}

QString HeadImg::userName() const { return m_userName; }
void HeadImg::setUserName(const QString & userName) 
{
    m_userName = userName;
    emit userNameChanged();
    m_v2 ? m_getV2() : m_get();
}

QString HeadImg::filePath() const { return m_filePath; }

void HeadImg::m_finished() 
{
    disconnect(&m_down, SIGNAL(finished()), this, SLOT(m_finished()));
    m_filePath = "file://" + QWXDIR + "/" + m_userName;
    emit filePathChanged(); 
}

void HeadImg::m_get() 
{
    QString url = WX_SERVER_HOST + WX_CGI_PATH + "webwxgeticon?seq=1388335457"
        "&username=" + m_userName;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString headImgPath = QWXDIR + "/" + m_userName;
    if (QFile::exists(headImgPath)) { 
        m_filePath = "file://" + QWXDIR + "/" + m_userName;
        emit filePathChanged();
    } else {
        m_down.get(url, headImgPath);
        connect(&m_down, SIGNAL(finished()), this, SLOT(m_finished()));
    }
}

void HeadImg::m_getV2()
{
    QString url = WX_V2_SERVER_HOST + WX_CGI_PATH + "webwxgeticon?seq=1388335457"
        "&username=" + m_userName;
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << url;
#endif
    QString headImgPath = QWXDIR + "/" + m_userName;
    if (QFile::exists(headImgPath)) {
        m_filePath = "file://" + QWXDIR + "/" + m_userName;
        emit filePathChanged();
    } else {
        m_down.get(url, headImgPath);
        connect(&m_down, SIGNAL(finished()), this, SLOT(m_finished()));
    }
}
