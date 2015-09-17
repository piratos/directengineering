#ifndef SYSTEMEVN_H
#define SYSTEMEVN_H

#include <QObject>
#include <QThread>
#include "tools.h"
#include "networkmanager.h"
#include <QMetaObject>
#include "keyboardmanager.h"
#include "downloadmanager.h"
#include "cookiesmanager.h"

class SystemeVN : public QObject
{
    Q_OBJECT
public:
    explicit SystemeVN();
    ~SystemeVN();
    void start();
private:
    QThread *threadNetworkManager,*threadKeyboardManager,*threadDownloadManager,*threadCookiesManager;
    Tools *tools;
    NetworkManager *networkManager;
    KeyboardManager *keyboardManager;
    DownloadManager *downloadManager;
    CookiesManager *cookiesManager;
};

#endif // SYSTEMEVN_H
