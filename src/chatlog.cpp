// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>                                                                   
#include <QDebug>

#include "chatlog.h"
#include "globaldeclarations.h"

ChatLog::ChatLog(QObject* parent) 
  : QObject(parent)
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

ChatLog::~ChatLog() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
    foreach (QObject* obj, m_chatLogList) {
        if (obj) {
            delete obj;
            obj = nullptr;
        }
    }
    m_chatLogList.clear();
}

void ChatLog::load(QString toUserName) 
{
    QFile file(QWXDIR + "/" + toUserName + ".txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList result = line.split(" ");
            if (result.size() < 3)
                continue;

            m_chatLogList.append(new ChatLogObject(result[1], result[2]));
        }
        file.close();
    }
    emit chatLogListChanged();
}
