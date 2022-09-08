#ifndef TIMESHOW_H
#define TIMESHOW_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QEventLoop>
#include <QDebug>
#include <QTextCodec>
#include <QFile>


class TimeShow : public QObject
{
    Q_OBJECT
public:
    explicit TimeShow(QObject *parent = nullptr);

    void getWeather();

    void startGetWeather();

signals:
    void sendDateTime(QString dateTime);

    void sendTime(QString time, QString week);

    void sendNextTime(QString h, QString m, QString s);

    void getNextTime();

private:
    QString localAddr = "";//当前地址
    QString weather = "";//当前天气
    QString temperature = "";//当前气温


    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QNetworkRequest request;
    QEventLoop eventLoop;
    QByteArray data;
};

#endif // TIMESHOW_H
