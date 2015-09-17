#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>
#include <QByteArray>
#include <QDataStream>


class NetworkManager : public QObject
{
    Q_OBJECT
public:
    NetworkManager(QString id);
    ~NetworkManager();
public slots:
    void start();
    void sendData(QByteArray data);
private slots:
    void timeout();
    void disconnect(QAbstractSocket::SocketError e = QAbstractSocket::NetworkError);
private:
    QString identifiant;

    QTcpSocket *socket;
    QTimer *timer;

    QByteArray trameSeparation;
    QByteArray bufferToSend;

    void seConnecter();
    void envoyerTrame();
};

#endif // NETWORKMANAGER_H
