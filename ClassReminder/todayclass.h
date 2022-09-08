#ifndef TODAYCLASS_H
#define TODAYCLASS_H

#include <QObject>
#include <QString>
#include <QVector>

class TodayClass : public QObject
{
    Q_OBJECT
public:
    explicit TodayClass(QObject *parent = nullptr);
    QString name;
    QString classes[4] = {};
};

#endif // TODAYCLASS_H
