#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>
#include "course.h"

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);
    QString date[7] = {
        "星期一",
        "星期二",
        "星期三",
        "星期四",
        "星期五",
        "星期六",
        "星期日"
    };
    Course course[7] = {};
    QString name;
};

#endif // STUDENT_H
