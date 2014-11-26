// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef HEAD_IMG_H
#define HEAD_IMG_H

#include "download.h"

class HeadImg : public QObject 
{
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString filePath READ filePath NOTIFY filePathChanged)

public:
    HeadImg(QObject* parent = nullptr);
    ~HeadImg();

    QString userName() const;
    void setUserName(const QString & userName);

    QString filePath() const;

Q_SIGNALS:
    void userNameChanged();
    void filePathChanged();

private:
    QString m_userName;
    QString m_filePath;
    Download m_down;

private Q_SLOTS:
    void m_finished();

private:
    void m_get();
};

#endif // HEAD_IMG_H
