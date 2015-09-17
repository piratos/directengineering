#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>
#include <QProcess>
#include <QDir>
#include <QDateTime>

class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager();
public slots:
    void start();
    void timeout();
    void timeout2();
    void timeout3();
    void dataRecu(QNetworkReply* r);
private:
    QTimer *timer;
    QNetworkAccessManager *manager;
};

#endif // DOWNLOADMANAGER_H
