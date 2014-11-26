// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef DOWNLOAD_H
#define DOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QFile>

class Download : public QObject 
{
    Q_OBJECT

public:
    Download(QObject* parent = nullptr);
    ~Download();

    void get(QString url, QString filePath);

Q_SIGNALS:
    void downloaded(qreal progress);
    void finished();

private Q_SLOTS:
    void m_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void m_readyRead();
    void m_finished(QNetworkReply*);
    void m_sslErrors(QNetworkReply* reply, const QList<QSslError> & errors);

private:
    QNetworkAccessManager m_nam;
    QNetworkReply* m_reply;
    QFile m_file;
};

#endif // DOWNLOAD_H
