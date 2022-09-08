#ifndef CLASSFILE_H
#define CLASSFILE_H

#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVector>
#include <QDebug>

#include "student.h"

class ClassFile : public QObject
{
    Q_OBJECT
public:
    explicit ClassFile(QObject *parent = nullptr);
    QVector<Student*> students;

};

#endif // CLASSFILE_H
