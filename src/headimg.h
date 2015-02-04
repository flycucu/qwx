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

    bool v2() const { return m_v2; }
    void setV2(bool v2);

    QString userName() const { return m_userName; }
    void setUserName(const QString & userName);

    QString filePath() const { return m_filePath; }

Q_SIGNALS:
    void v2Changed();
    void userNameChanged();
    void filePathChanged();

private:
    void m_get(QString host);

private:
    bool m_v2;
    QString m_userName;
    QString m_filePath;
    Download m_downLoad;
    QMetaObject::Connection m_connection;
};

#endif // HEAD_IMG_H
