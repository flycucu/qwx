// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include "clipboard.h"
#include <QApplication>
#include <QMimeData>
#include <QDebug>

Clipboard::Clipboard(QObject *parent)
    : QObject(parent)
    , m_clipboard(QApplication::clipboard())
{
    connect(m_clipboard, SIGNAL(dataChanged()), this, SLOT(dataChanged()));
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

void Clipboard::dataChanged()
{
}
