// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include "process.h"

#include <QtCore/QProcess>
#include <QDebug>

class Process::Private : public QProcess
{
    Q_OBJECT
public:
    Private(Process *parent);

    QString program;
    QStringList arguments;
    QString dir;
private:
    Process *q;
};

Process::Private::Private(Process *parent)
    : QProcess(parent)
    , q(parent)
{
    connect(this, SIGNAL(started()), q, SIGNAL(started()));
    connect(this, SIGNAL(finished(int,QProcess::ExitStatus)), q, SIGNAL(finished(int)));
    connect(this, SIGNAL(readyReadStandardOutput()), q, SIGNAL(readyReadStandardOutput()));
    connect(this, SIGNAL(readyReadStandardError()), q, SIGNAL(readyReadStandardError()));
}

Process::Process(QObject *parent)
    : QObject(parent)
    , d(new Private(this))
{
}

Process::~Process()
{
}

const QString &Process::program() const
{
    return d->program;
}

void Process::setProgram(const QString &program)
{
    if (program == d->program) return;
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << program;
    d->program = program;
    emit programChanged(d->program);
}

const QStringList &Process::arguments() const
{
    return d->arguments;
}

void Process::setArguments(const QStringList &arguments)
{
    if (arguments == d->arguments) return;
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << arguments;
    d->arguments = arguments;
    emit argumentsChanged(d->arguments);
}

const QString &Process::dir() const { return d->dir; }

void Process::setDir(const QString &dir) 
{
    if (dir == d->dir) return;
    d->dir = dir;
    d->setWorkingDirectory(d->dir);
    emit dirChanged();
}

void Process::start()
{
    d->start(d->program, d->arguments);
}

void Process::terminate()
{
    d->terminate();
}

void Process::kill()
{
    d->kill();
}

QByteArray Process::readAllStandardError()
{
    return d->readAllStandardError();
}

QByteArray Process::readAllStandardOutput()
{
    return d->readAllStandardOutput();
}

#include "process.moc"
