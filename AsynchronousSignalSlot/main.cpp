#include <QCoreApplication>
#include <QNetworkReply>
#include <QDebug>
#include<QNetworkAccessManager>

void printHTML (QString html){
    qDebug()<<"Done";
    qDebug()<<html;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString *html = new QString;
    qDebug() << "Start";
    QNetworkAccessManager manager;
    QNetworkRequest req(QUrl ("http://www.dustyfeet.com"));
    QNetworkReply* reply = manager.get(req);

    QObject::connect(reply,&QNetworkReply::readyRead,[=](){
        html->append(QString(reply->readAll()));
    });
    QObject::connect(reply,&QNetworkReply::downloadProgress,[](qint64 bytesReceived, qint64 bytesTotal){
        qDebug()<< "Progress: " << bytesReceived << "bytes /"
                 << bytesTotal << "bytes";
    });
    QObject::connect(reply,&QNetworkReply::finished,[=](){
        printHTML(*html);
    });

    return a.exec();
}
