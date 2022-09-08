#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QRect>
#include <QScreen>
#include <QDesktopWidget>
#include <QTextToSpeech>
#include <QLabel>

#include "timeshow.h"
#include "classfile.h"
#include "todayclass.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void windowInit();

    int getWeek(QString week);

public slots:
    void getDateTime(QString dateTime);

    void classTip(QString time, QString week);

    void showNextClass(QString h, QString m, QString s);

signals:
    void sendNextTime();

private:
    Ui::MainWindow *ui;
    int height;
    QVector<Student*> students;
    QTextToSpeech *tts;
    QVector<TodayClass*> todayClasses;
    QVector<QLabel*> nextLabels;
    int weekNumber;
};
#endif // MAINWINDOW_H
