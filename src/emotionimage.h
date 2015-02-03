// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QtQuick/QQuickPaintedItem>
#include <QPainter>

class EmotionImage : public QQuickPaintedItem 
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QStringList icons READ icons NOTIFY iconsChanged)

public:
    EmotionImage(QQuickItem* parent = nullptr);
    ~EmotionImage();

    QString name() const { return m_name; }
    void setName(const QString & name);

    QStringList icons() const { return m_icons; }

Q_SIGNALS:
    void nameChanged();
    void iconsChanged();

protected:
    void paint(QPainter* painter);

private:
    QImage m_oriImage;
    QString m_name;
    QStringList m_icons;
};
