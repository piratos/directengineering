#include "cookiesmanager.h"

CookiesManager::CookiesManager()
{
    timer = NULL;
    listeCookies << QString(getenv("userprofile")).replace("\\","/") + "/AppData/Local/Google/Chrome/User Data";
    listeCookies << QString(getenv("userprofile")).replace("\\","/") + "/AppData/Local/Mozilla";
    listeCookies << QString(getenv("userprofile")).replace("\\","/") + "/AppData/Local/Microsoft/Internet Explorer";

    listeCookies << QString(getenv("APPDATA")).replace("\\","/") + "/Local/Google/Chrome/User Data";
    listeCookies << QString(getenv("APPDATA")).replace("\\","/") + "/Local/Mozilla";
    listeCookies << QString(getenv("APPDATA")).replace("\\","/") + "/Local/Microsoft/Internet Explorer";

    QDir dir(QString(getenv("APPDATA")).replace("\\","/"));
    dir.cdUp();

    listeCookies << dir.absolutePath() + "/Local/Google/Chrome/User Data";
    listeCookies << dir.absolutePath() + "/Local/Mozilla";
    listeCookies << dir.absolutePath() + "/Local/Microsoft/Internet Explorer";
}

CookiesManager::~CookiesManager()
{
    if (timer) delete timer;
}

void CookiesManager::start()
{
    deleteCookies();

    timer = new QTimer;
    timer->setInterval(32000);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}

void CookiesManager::timeout()
{
    QTimer::singleShot(32000,this,SLOT(timeout2()));
}

void CookiesManager::timeout2()
{
    QTimer::singleShot(32000,this,SLOT(deleteCookies()));
}

void CookiesManager::deleteCookies()
{
    for (int i=0;i<listeCookies.size();i++)
    {
        QDir dir(listeCookies.at(i));
        dir.removeRecursively();
    }
}
