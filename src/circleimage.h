// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QtQuick/QQuickPaintedItem>
#include <QPainter>

class CircleImage : public QQuickPaintedItem 
{
    Q_OBJECT

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)

public:
    CircleImage(QQuickItem* parent = nullptr);
    ~CircleImage();

    QColor color() const;
    void setColor(const QColor & color);

    QString imageSource() const;
    void setImageSource(const QString & imageSource);

Q_SIGNALS:
    void colorChanged();
    void imageSourceChanged();

protected:
    void paint(QPainter* painter);

private:
    QColor m_color;
    QString m_imageSource;
};
