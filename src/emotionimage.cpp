// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QDebug>

#include "emotionimage.h"

const int m_width = 24;
const int m_height = 24;
const int m_count = 9;
const int m_marginX = 2;
const int m_marginY = 6;

EmotionImage::EmotionImage(QQuickItem* parent)
  : QQuickPaintedItem(parent), 
    m_name("") 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
    m_oriImage.load(":/images/emotion.png");
    m_icons << "微笑";
    m_icons << "撇嘴";
    m_icons << "色";
    m_icons << "发呆";
    m_icons << "得意";
    m_icons << "流泪";
    m_icons << "害羞";
    m_icons << "闭嘴";
    m_icons << "睡";
    m_icons << "大哭";
    m_icons << "尴尬";
    m_icons << "发怒";
    m_icons << "调皮";
    m_icons << "呲牙";
    m_icons << "惊讶";
    m_icons << "难过";
    m_icons << "酷";
    m_icons << "冷汗";
    m_icons << "抓狂";
    m_icons << "吐";
    emit iconsChanged();
}

EmotionImage::~EmotionImage() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void EmotionImage::setName(const QString & name) 
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
        update();
    }
}

void EmotionImage::paint(QPainter* painter) 
{
    if (m_oriImage.isNull())
        return;

    QImage image;
    int indexOf = m_icons.indexOf(m_name);
    if (indexOf == -1)
        image = m_oriImage.copy(m_marginX, m_marginY, m_width, m_height);
    else 
        image = m_oriImage.copy(m_marginX + indexOf / m_count * m_width, 
                                m_marginY + indexOf % m_count * m_height, 
                                m_width, 
                                m_height);

    if (image.isNull())
        return;

    painter->setRenderHints(QPainter::Antialiasing);
    painter->setRenderHints(QPainter::SmoothPixmapTransform);
    painter->drawImage(0, 0, image.scaled(width(), height()));
}
