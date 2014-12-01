// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include "circleimage.h"

CircleImage::CircleImage(QQuickItem* parent)
  : QQuickPaintedItem(parent), 
    m_color(Qt::white), 
    m_imageSource("") 
{
}

CircleImage::~CircleImage() 
{
}

QColor CircleImage::color() const { return m_color; }
void CircleImage::setColor(const QColor & color) 
{
    if (m_color != color) {
        m_color = color;
        emit colorChanged();
        update();
    }
}

QString CircleImage::imageSource() const { return m_imageSource; }
void CircleImage::setImageSource(const QString & imageSource) 
{
    if (m_imageSource != imageSource) {
        m_imageSource = imageSource;
        if (m_imageSource.contains("qrc:/qml")) 
            m_imageSource.replace("qrc:/qml", ":");
        else if (m_imageSource.contains("file://")) 
            m_imageSource.replace("file://", "");
        emit imageSourceChanged();
        update();
    }
}

void CircleImage::paint(QPainter* painter) 
{
    QImage image(m_imageSource);
    QPainterPath path;
    path.addRect(0, 0, width(), height());
    path.addEllipse(0, 0, width(), height());
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setRenderHints(QPainter::SmoothPixmapTransform);
    painter->drawImage(0, 0, image.scaled(width(), height()));
    painter->fillPath(path, QBrush(m_color));
}
