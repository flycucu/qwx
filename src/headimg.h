// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef HEAD_IMG_H
#define HEAD_IMG_H

#include "download.h"

class HeadImg : public QObject 
{
    Q_OBJECT

    Q_PROPERTY(bool v2 READ v2 WRITE setV2 NOTIFY v2Changed)
    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString filePath READ filePath NOTIFY filePathChanged)

public:
    HeadImg(QObject* parent = nullptr);
    ~HeadImg();

    bool v2() const;
    void setV2(bool v2);

    QString userName() const;
    void setUserName(const QString & userName);

    QString filePath() const;

Q_SIGNALS:
    void v2Changed();
    void userNameChanged();
    void filePathChanged();

private:
    bool m_v2;
    QString m_userName;
    QString m_filePath;
    Download m_down;

private Q_SLOTS:
    void m_finished();

private:
    void m_get();
    void m_getV2();
};

#endif // HEAD_IMG_H
