// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include "clipboard.h"
#include <QApplication>
#include <QMimeData>
#include <QDebug>

Clipboard::Clipboard(QObject *parent)
    : QObject(parent)
    , m_clipboard(QApplication::clipboard())
{
#if QWX_DEBUG
    qDebug() << __PRETTY_FUNCTION__;
#endif
}

QString Clipboard::text()
{
    return m_clipboard->text();
}

void Clipboard::copy(QString text)
{
    // Fill a mimeData object
    QMimeData* mimeData = new QMimeData();
    mimeData->setText(text);

    // Let the clipboard know of our mimeData object
    m_clipboard->setMimeData(mimeData);
}
