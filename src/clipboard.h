// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <QObject>
#include <QClipboard>
#include <QStringList>

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

    /**
     * Yeah, our workaround function.. It is better in Qt 5 since arrays in properties work
     * properly there.
     */
    Q_INVOKABLE QStringList urlList() { return m_urlList; }
    
public slots:
    void dataChanged();
    
private:
    QClipboard* m_clipboard;
    QStringList m_urlList; // Required for Qt 4.8 since it can't properly define arrays. It can in JS, not in property ...
};

#endif // CLIPBOARD_H
