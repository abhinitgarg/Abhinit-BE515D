#include "networkmanager.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>
#include <QDateTime>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    connect(manager,SIGNAL(finished(QNetworkReply*)), this, SLOT(myReplyFinished(QNetworkReply*)));
}

// To load the data
    void NetworkManager::loadWebPage(){
    QNetworkRequest request;

    QString apiKey = "demo";
    QString urlString = QString("https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=MSFT&apikey=%0").arg(apiKey);

    QUrl url(urlString);

    request.setUrl(url);

    QNetworkReply *reply = manager->get(request);

}

// to read the data
void NetworkManager::myReplyFinished(QNetworkReply*reply)
{
    QByteArray webData = reply->readAll();

    // To store the file
     QFile *file = new QFile(QDir::currentPath() + "\\DATA.txt");
     if(file->open(QFile::Append))
         {
           file->write(webData);
           file->flush();
           file->close();
         }
     delete file;

     QList<QPair<QString,QString>> graphValues;
     QList<QPair<QString,QString>> graphValues1;
     QList<QPair<QString,QString>> graphValues2;


    QJsonDocument document = QJsonDocument::fromJson(webData);

    if(document.isArray() == true){
        //retreive the array
        QJsonArray rootArray = document.array();
    }

    else if(document.isObject() == true)
    {

        QJsonObject rootObject = document.object();

        QJsonObject timeSeries = rootObject["Time Series (Daily)"].toObject();
        QStringList keys = timeSeries.keys();

        for (QString k : keys){
            QJsonObject dayValues = timeSeries[k].toObject();
            QString closeValue = dayValues["5. volume"].toString();
            QString HighValue = dayValues["4. close"].toString();


            QPair<QString,QString> dataItem1;
             dataItem1.first = k;
             dataItem1.second = closeValue;

             QPair<QString,QString> dataItem2;
              dataItem2.first = k;
              dataItem2.second = HighValue;

            graphValues1.append(dataItem1);
            graphValues2.append(dataItem2);
        }

   }



    for (int i=0; i<graphValues1.size(); i++)
    {
        QPair<QString,QString> data = graphValues1[i];
        qDebug()<<data.first <<" - "<<data.second;
        float list=data.second.toFloat();
        QDateTime xAxisValue; xAxisValue.setDate(QDate::fromString(data.first,"yyyy-MM-dd"));
        xAxisValue.toMSecsSinceEpoch();
        emit valueUpdated2(QVariant(xAxisValue),QVariant(list));
 }

    for (int i=0; i<graphValues2.size(); i++)
    {
        QPair<QString,QString> data = graphValues2[i];
        qDebug()<<data.first <<" - "<<data.second;
        float list=data.second.toFloat();
        QDateTime xAxisValue; xAxisValue.setDate(QDate::fromString(data.first,"yyyy-MM-dd"));
        xAxisValue.toMSecsSinceEpoch();
        emit valueUpdated3(QVariant(xAxisValue),QVariant(list));
    }


}
