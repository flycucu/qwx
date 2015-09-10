// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QClipboard>

class Clipboard : public QObject
{
    Q_OBJECT

public:
    explicit Clipboard(QObject *parent = nullptr);

    Q_INVOKABLE QString text();

    /**
     * This is just to put text on the clipboard.
     */
    Q_INVOKABLE void copy(QString text);
    
private:
    QClipboard* m_clipboard;
};

#endif // CLIPBOARD_H
