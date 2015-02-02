// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef CHATLOG_H
#define CHATLOG_H

#include <QObject>

class ChatLogObject;

class ChatLog : public QObject 
{
    Q_OBJECT

    Q_PROPERTY(QList<QObject*> chatLogList READ chatLogList NOTIFY chatLogListChanged)

public:
    explicit ChatLog(QObject* parent = nullptr);
    ~ChatLog();

    QList<QObject*> chatLogList() const { return m_chatLogList; }

    Q_INVOKABLE void load(QString toUserName);

Q_SIGNALS:
    void chatLogListChanged();

private:
    QList<QObject*> m_chatLogList;
};

class ChatLogObject : public QObject 
{
    Q_OBJECT

    Q_PROPERTY(QString userName READ userName WRITE setUserName NOTIFY userNameChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)

public:
    ChatLogObject(const QString & userName, 
                  const QString & content) 
      : m_userName(userName), m_content(content)
    {
    }

    QString userName() const { return m_userName; }
    void setUserName(const QString & userName) 
    {
        m_userName = userName;
        emit userNameChanged();
    }

    QString content() const { return m_content; }
    void setContent(const QString & content) 
    {
        m_content = content;
        emit contentChanged();
    }

Q_SIGNALS:
    void userNameChanged();
    void contentChanged();

private:
    QString m_userName;
    QString m_content;
};

#endif // CHATLOG_H
