#ifndef WHOAMI_H
#define WHOAMI_H

#include <QObject>
#include <QDir>
#include <QDate>
#include <QTime>
#include <QFile>
#include <QApplication>
#include <QSettings>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDataStream>

class Tools : public QObject
{
    Q_OBJECT
public:
    explicit Tools();
    QString getUserName();
    QString getComputerName();
    QString getRootPath();
    QString getIdentifiant();
    QString getHasard(int nbr);
    QString getProgramFile();
    bool copyMe(QString directory, QString filePath);
public slots:
    void makeMeAtStartup();
    void makeTrace();
private:
    QString identifiant;
};

#endif // WHOAMI_H
