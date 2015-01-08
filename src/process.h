// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef PROCESS_H
#define PROCESS_H

#include <QtCore/QObject>
#include <QtCore/QStringList>

class Process : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Process)
    Q_PROPERTY(QString program READ program WRITE setProgram NOTIFY programChanged)
    Q_PROPERTY(QStringList arguments READ arguments WRITE setArguments NOTIFY argumentsChanged)
    Q_PROPERTY(QString dir READ dir WRITE setDir NOTIFY dirChanged)

    public:
    Process(QObject *parent = 0);
    ~Process();

    const QString &program() const;
    const QStringList &arguments() const;
    const QString &dir() const;

    Q_INVOKABLE QByteArray readAllStandardError();
    Q_INVOKABLE QByteArray readAllStandardOutput();

public slots:
    void setProgram(const QString &program);
    void setArguments(const QStringList &arguments);
    void setDir(const QString &dir);

    void start();
    void terminate();
    void kill();

signals:
    void programChanged(const QString &program);
    void argumentsChanged(const QStringList &arguments);
    void dirChanged();

    void finished(int exitCode);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();

private:
    class Private;
    Private *d;
};

#endif // PROCESS_H
