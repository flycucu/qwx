// Copyright (C) 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef EMOTION_H
#define EMOTION_H

#include <QAbstractListModel>

class EmotionObject;

class Emotion : public QAbstractListModel 
{
    Q_OBJECT

public:
    enum EmotionRoles {
        TitleRole = Qt::UserRole + 1,
        NameRole
    };                                                                          

    explicit Emotion(QObject* parent = nullptr);
    ~Emotion();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const; 

    void addEmotion(const EmotionObject & emotion);                    

protected:                                                                         
    QHash<int, QByteArray> roleNames() const;

private:
    QList<EmotionObject> m_emotions;
};

class EmotionObject 
{
public:
    EmotionObject(const QString & title, const QString & name)
      : m_title(title), m_name(name)
    {
    }

    const QString title() const { return m_title; }
    const QString name() const { return m_name; }

private:
    QString m_title;
    QString m_name;
};

#endif  // EMOTION_H
