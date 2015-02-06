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
            QStringList result = line.split(DELIM);
            if (result.size() < 3)
                continue;
 
            QString userName = result[1];
            QString content = result[2];
            if (content.startsWith("@")) {
                userName = content.left(content.indexOf(":<br/>"));
                content = content.mid(content.indexOf(":<br/>") + QString(":<br/>").size()); 
            }
            m_chatLogList.append(new ChatLogObject(userName, content));
        }
        file.close();
    }
    emit chatLogListChanged();
}
