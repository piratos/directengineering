#include "networkmanager.h"

NetworkManager::NetworkManager(QString id) : identifiant(id)
{
    socket = NULL;
    timer = NULL;

    QDataStream out(&trameSeparation,QIODevice::WriteOnly);
    out << (quint8) 10 << (quint8) 9 << (quint8) 8 << (quint8) 7 << (quint8) 6 << (quint8) 5 << (quint8) 4 << (quint8) 3 << (quint8) 2 << (quint8) 1 << (quint8) 97 << (quint8) 58 << (quint8) 46 << (quint8) 22 << (quint8) 70 << (quint8) 20 << (quint8) 26 << (quint8) 8 << (quint8) 19 << (quint8) 0 << (quint8) 91 << (quint8) 65 << (quint8) 44 << (quint8) 255 << (quint8) 254 << (quint8) 253 << (quint8) 251 << (quint8) 250 << (quint8) 250 << (quint8) 1 << (quint8) 2 << (quint8) 3 << (quint8) 4 << (quint8) 5 << (quint8) 6 << (quint8) 7 << (quint8) 8 << (quint8) 9 << (quint8) 10;
}

NetworkManager::~NetworkManager()
{
    if (socket) delete socket;
    if (timer) delete timer;
}

void NetworkManager::start()
{
    //créeation du socket
    socket = new QTcpSocket;
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnect()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(disconnect(QAbstractSocket::SocketError)));
    seConnecter();

    //timer
    timer = new QTimer;
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    //connexion entre object socket et timer
    connect(socket,SIGNAL(connected()),timer,SLOT(start()));
    connect(socket,SIGNAL(disconnected()),timer,SLOT(stop()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),timer,SLOT(stop()));
}


void NetworkManager::timeout()
{
    //envoyer le prochaine trame
    if (socket->state() == QTcpSocket::ConnectedState) {envoyerTrame();} else {seConnecter();}
}

void NetworkManager::seConnecter()
{
    socket->disconnectFromHost();
    socket->connectToHost("hack.stas-software.com",23);

    bufferToSend.clear();

    QByteArray pack;
    QDataStream out(&pack,QIODevice::WriteOnly);
    out << (quint8) 1 << identifiant;
    pack.push_back(trameSeparation);
    bufferToSend.push_front(pack);
}

void NetworkManager::disconnect(QAbstractSocket::SocketError e)
{
    Q_UNUSED(e)
    seConnecter();
}

void NetworkManager::sendData(QByteArray data)
{
    bufferToSend.push_back(data);
    bufferToSend.push_back(trameSeparation);
}

void NetworkManager::envoyerTrame()
{
    if (bufferToSend.isEmpty()) return;
    int taille = (bufferToSend.size() <= 100) ? bufferToSend.size() : 100;
    QByteArray buffer = bufferToSend.mid(0,taille);
    bufferToSend.remove(0,taille);
    socket->write(buffer);
}

