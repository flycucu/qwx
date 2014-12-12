// Copyright (C) 2014 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QFile>
#include <QDebug>

#include "idiom.h"
#include "globaldeclarations.h"

const int WORD_SIZE = 5;

Idiom::Idiom(QObject* parent) 
  : QObject(parent), 
    m_eng(time(NULL))
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
    QFile file(":/src/dict.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        while (!file.atEnd()) {
            QString line = QString(file.readLine());
            if (line.size() < WORD_SIZE) continue;

            QString lineFirstStr = line.left(1);
            if (m_dict.find(lineFirstStr) != m_dict.end()) 
                m_dict[lineFirstStr].push_back(line);
            else {
                Array words; words.push_back(line);
                m_dict[lineFirstStr] = words;
            }
        }
        file.close();
    }
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << m_dict.size();
#endif
}

Idiom::~Idiom() 
{
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__;
#endif
    m_dict.clear();
}

QString Idiom::get(QString word) 
{ 
    QString search = word.mid(3, 4);
#if QWX_DEBUG
    qDebug() << "DEBUG:" << __PRETTY_FUNCTION__ << search;
#endif
    if (m_dict.find(search) != m_dict.end()) {
        std::uniform_int_distribution<int> index(0, m_dict[search].size() - 1);
        return m_dict[search][index(m_eng)];
    }
    return "";
}

