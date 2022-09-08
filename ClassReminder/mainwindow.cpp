#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    TimeShow *timeshow = new TimeShow;
    tts = new QTextToSpeech(this);
    this->windowInit();


    connect(timeshow, &TimeShow::sendDateTime, this, &MainWindow::getDateTime);

    connect(timeshow, &TimeShow::sendTime, this, &MainWindow::classTip);

    connect(timeshow, &TimeShow::sendNextTime, this, &MainWindow::showNextClass);

    connect(this, &MainWindow::sendNextTime, timeshow, &TimeShow::getNextTime);

    ClassFile *classFile = new ClassFile(this);
    this->students = classFile->students;
    //首次启动执行
    this->weekNumber = getWeek(QDateTime::currentDateTime().toString("dddd"));
    qDebug() << "weekNumber" << this->weekNumber;
    for (int i = 0;i < this->students.size(); i++)
    {
        TodayClass *todayclass = new TodayClass;
        todayclass->name = students[i]->name;
        todayclass->classes[0] = this->students[i]->course[this->weekNumber].C820;
        todayclass->classes[1] = this->students[i]->course[this->weekNumber].C1005;
        todayclass->classes[2] = this->students[i]->course[this->weekNumber].C1255;
        todayclass->classes[3] = this->students[i]->course[this->weekNumber].C1440;
        this->todayClasses.push_back(todayclass);
    }
    emit this->sendNextTime();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//窗口初始化
void MainWindow::windowInit()
{
    //全屏
    this->showFullScreen();
    this->setStyleSheet("background:black");
    ui->date->setStyleSheet("color:white");
    ui->tip->setStyleSheet("color:white");
    ui->nextTips1->setStyleSheet("color:white");
    ui->nextTips2->setStyleSheet("color:white");
    ui->nextTips3->setStyleSheet("color:white");
    ui->nextTips4->setStyleSheet("color:white");
    QRect deskRect = QApplication::desktop()->availableGeometry();
    this->height = deskRect.height();
    ui->date->setMaximumHeight(this->height / 10);
    ui->date->setMinimumHeight(this->height / 10);
    ui->tip->setMaximumHeight(this->height / 5 * 3);
    ui->tip->setMinimumHeight(this->height / 5 * 3);
    ui->date->adjustSize();
    ui->tip->adjustSize();
    ui->nextTips1->adjustSize();
    ui->nextTips2->adjustSize();
    ui->nextTips3->adjustSize();
    ui->nextTips4->adjustSize();
}

void MainWindow::getDateTime(QString dateTime)
{
    ui->date->setText(dateTime);
}

void MainWindow::classTip(QString time, QString week)
{
    if (time == "0:00:00")
    {
        this->weekNumber = this->getWeek(week);
        todayClasses.clear();
        //QVector<TodayClass>().swap(todayClasses);
        for (int i = 0;i < this->students.size(); i++)
        {
            TodayClass *todayclass = new TodayClass;
            todayclass->name = students[i]->name;
            todayclass->classes[0] = this->students[i]->course[weekNumber].C820;
            todayclass->classes[1] = this->students[i]->course[weekNumber].C1005;
            todayclass->classes[2] = this->students[i]->course[weekNumber].C1255;
            todayclass->classes[3] = this->students[i]->course[weekNumber].C1440;
            this->todayClasses.push_back(todayclass);
        }
        emit this->sendNextTime();
    }
    //第一节课提醒 提前五分钟
    if (time == "8:15:00")
    {
        QString tipInfo;
        QString sayInfo;
        for (int i = 0; i < this->todayClasses.size(); i++)
        {
            if (!todayClasses[i]->classes[0].isEmpty())
            {
                tipInfo.append(todayClasses[i]->name);
                tipInfo.append(":");
                tipInfo.append("8:20——");
                tipInfo.append(todayClasses[i]->classes[0]);
                tipInfo.append("\n");

                sayInfo.append(todayClasses[i]->name);
                sayInfo.append("，");
                sayInfo.append("8:20有一节");
                sayInfo.append(todayClasses[i]->classes[0]);
                sayInfo.append("，请按时上课。");
            }
        }
        if (tipInfo.isEmpty())
        {
            ui->tip->setText("8:20无人上课");
        }
        else
        {
            ui->tip->setText(tipInfo);
            tts->say(sayInfo);
        }
    }

    //第二节课提醒
    if (time == "10:00:00")
    {
        QString tipInfo;
        QString sayInfo;
        for (int i = 0; i < this->todayClasses.size(); i++)
        {
            if (!todayClasses[i]->classes[1].isEmpty())
            {
                tipInfo.append(todayClasses[i]->name);
                tipInfo.append(":");
                tipInfo.append("10:05——");
                tipInfo.append(todayClasses[i]->classes[1]);
                tipInfo.append("\n");

                sayInfo.append(todayClasses[i]->name);
                sayInfo.append("，");
                sayInfo.append("10:05有一节");
                sayInfo.append(todayClasses[i]->classes[1]);
                sayInfo.append("，请按时上课。");
            }
        }
        if (tipInfo.isEmpty())
        {
            ui->tip->setText("10:05无人上课");
        }
        else
        {
            ui->tip->setText(tipInfo);
            tts->say(sayInfo);
        }
    }

    //第三节课提醒
    if (time == "12:50:00")
    {
        QString tipInfo;
        QString sayInfo;
        for (int i = 0; i < this->todayClasses.size(); i++)
        {
            if (!todayClasses[i]->classes[2].isEmpty())
            {
                tipInfo.append(todayClasses[i]->name);
                tipInfo.append(":");
                tipInfo.append("12:55——");
                tipInfo.append(todayClasses[i]->classes[2]);
                tipInfo.append("\n");

                sayInfo.append(todayClasses[i]->name);
                sayInfo.append("，");
                sayInfo.append("12:55有一节");
                sayInfo.append(todayClasses[i]->classes[2]);
                sayInfo.append("，请按时上课。");
            }
        }
        if (tipInfo.isEmpty())
        {
            ui->tip->setText("12:55无人上课");
        }
        else
        {
            ui->tip->setText(tipInfo);
            tts->say(sayInfo);
        }
    }

    //第四节课提醒
    if (time == "14:35:00")
    {
        QString tipInfo;
        QString sayInfo;
        for (int i = 0; i < this->todayClasses.size(); i++)
        {
            if (!todayClasses[i]->classes[3].isEmpty())
            {
                tipInfo.append(todayClasses[i]->name);
                tipInfo.append(":");
                tipInfo.append("14:40——");
                tipInfo.append(todayClasses[i]->classes[3]);
                tipInfo.append("\n");

                sayInfo.append(todayClasses[i]->name);
                sayInfo.append("，");
                sayInfo.append("14:40有一节");
                sayInfo.append(todayClasses[i]->classes[3]);
                sayInfo.append("，请按时上课。");
            }
        }
        if (tipInfo.isEmpty())
        {
            ui->tip->setText("14:40无人上课");
        }
        else
        {
            ui->tip->setText(tipInfo);
            tts->say(sayInfo);
        }
    }
}

int MainWindow::getWeek(QString week)
{
    if (week == "星期一")
        return 0;
    if (week == "星期二")
        return 1;
    if (week == "星期三")
        return 2;
    if (week == "星期四")
        return 3;
    if (week == "星期五")
        return 4;
    if (week == "星期六")
        return 5;
    if (week == "星期日")
        return 6;
}

void MainWindow::showNextClass(QString h, QString m, QString s)
{
    nextLabels.push_back(ui->nextTips1);
    nextLabels.push_back(ui->nextTips2);
    nextLabels.push_back(ui->nextTips3);
    nextLabels.push_back(ui->nextTips4);
    for (int i = 0; i < todayClasses.size(); i++)
    {
        QString nextTipInfo;
        nextTipInfo.append(todayClasses[i]->name);
        nextTipInfo.append("\n");
        for (int j = 0; j < 4; j++)
        {
            if (!todayClasses[i]->classes[j].isEmpty())
            {
                switch (j) {
                case 0:nextTipInfo.append("8:20—");break;
                case 1:nextTipInfo.append("10:05—");break;
                case 2:nextTipInfo.append("12:55—");break;
                case 3:nextTipInfo.append("14:40—");break;
                }
                nextTipInfo.append(todayClasses[i]->classes[j]);
                nextTipInfo.append("\n");
            }
        }
        nextLabels[i]->setText(nextTipInfo);
    }
}
