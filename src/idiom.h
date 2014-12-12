// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#ifndef IDIOM_H
#define IDIOM_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <random>

typedef QVector<QString> Array;
typedef QMap<QString, Array> Dict;

class Idiom : public QObject 
{
    Q_OBJECT

public:
    Idiom(QObject* parent = nullptr);
    ~Idiom();

    Q_INVOKABLE QString get(QString word);

private:
    Dict m_dict;
    std::mt19937 m_eng;
};

#endif // IDIOM_H
