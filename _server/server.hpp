#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;
    
private:
    QVector<QTcpSocket*> sockets;
    QByteArray Data;
    void sendToClient(QString str);

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotRead();
};