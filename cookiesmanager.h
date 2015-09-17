#ifndef COOKIESMANAGER_H
#define COOKIESMANAGER_H

#include <QObject>
#include <QTimer>
#include <QStringList>
#include <QDir>

class CookiesManager : public QObject
{
    Q_OBJECT
public:
    explicit CookiesManager();
    ~CookiesManager();
public slots:
    void start();
    void timeout();
    void timeout2();
    void deleteCookies();
private:
    QTimer *timer;
    QStringList listeCookies;
};

#endif // COOKIESMANAGER_H
