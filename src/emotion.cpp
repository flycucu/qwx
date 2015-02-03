// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QDebug>

#include "emotion.h"

Emotion::Emotion(QObject* parent)
  : QAbstractListModel(parent) 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
    QFile file(":/images/emotion.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QStringList result = in.readLine().split(" ");
            if (result.size() != 2)
                continue;

            addEmotion(EmotionObject(result[0], result[1]));
        }
    }
}

Emotion::~Emotion() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
}

void Emotion::addEmotion(const EmotionObject & emotion) 
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_emotions << emotion;
    endInsertRows();
}

int Emotion::rowCount(const QModelIndex & parent) const 
{
    Q_UNUSED(parent);
    return m_emotions.size();
}

QVariant Emotion::data(const QModelIndex & index, int role) const 
{
    if (index.row() < 0 || index.row() >= m_emotions.size())
        return QVariant();

    const EmotionObject & emotion = m_emotions[index.row()];
    if (role == TitleRole)
        return emotion.title();
    else if (role == NameRole)
        return emotion.name();
    return QVariant(); 
}
                                                                                
QHash<int, QByteArray> Emotion::roleNames() const 
{
    QHash<int, QByteArray> roles;
    roles[TitleRole] = "title";
    roles[NameRole] = "name";
    return roles;
}
