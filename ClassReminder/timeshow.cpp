#include "timeshow.h"

TimeShow::TimeShow(QObject *parent) : QObject(parent)
{
    this->getWeather();
    QTimer *timer = new QTimer(this);
    timer->setInterval(1000);
    timer->start();
    connect(timer, &QTimer::timeout, this, [=](){
        QString timeData = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss dddd");
        timeData.append("\t");
        timeData.append(this->localAddr);
        timeData.append("\t");
        timeData.append(this->weather);
        timeData.append("\t");
        timeData.append(this->temperature);
        if (!this->temperature.isEmpty())
        {
            timeData.append("°");
        }
        emit sendDateTime(timeData);
        emit sendTime(QDateTime::currentDateTime().toString("hh:mm:ss"), QDateTime::currentDateTime().toString("dddd"));
    });
    QTimer *timer1 = new QTimer(this);
    timer1->setInterval(20000);
    timer1->start();

    connect(timer1, &QTimer::timeout, this, &TimeShow::startGetWeather);

    reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [&](){
        this->data = reply->readAll();

        QJsonDocument doc = QJsonDocument::fromJson(this->data);
        QJsonObject object = doc.object();
        if (object.contains("results") && object["results"].isArray())
        {
            QJsonArray arr = object["results"].toArray();
            this->localAddr = arr[0].toObject().take("location").toObject().take("name").toString();
            this->weather = arr[0].toObject().take("now").toObject().take("text").toString();
            this->temperature = arr[0].toObject().take("now").toObject().take("temperature").toString();
        }
    });

    connect(this, &TimeShow::getNextTime, this, [=](){
        emit sendNextTime(QDateTime::currentDateTime().toString("hh"),
                          QDateTime::currentDateTime().toString("mm"),
                          QDateTime::currentDateTime().toString("ss"));
    });
}


void TimeShow::getWeather()
{
    manager = new QNetworkAccessManager(this);
    QUrl url("https://api.seniverse.com/v3/weather/now.json");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("key", "Sa-atVRsvAIV4Egcl");
    urlQuery.addQueryItem("location", "haerbin");
    urlQuery.addQueryItem("language", "zh-Hans");
    urlQuery.addQueryItem("unit", "c");
    url.setQuery(urlQuery);
    request.setUrl(url);

    //https支持
    QSslConfiguration config;
    QSslConfiguration conf = request.sslConfiguration();
    conf.setPeerVerifyMode(QSslSocket::VerifyNone);
    conf.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(conf);
}

void TimeShow::startGetWeather()
{
    reply = manager->get(request);
    //QTimer::singleShot(5000, &eventLoop, [&](){ if(eventLoop.isRunning()) { eventLoop.quit(); } });
}
