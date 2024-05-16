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
    void sendToClient(const QString str);
    bool parseMessage(QString message, int& inPort);
    int port;

public slots:
    void onSubmitClk(const QString message);
    void incomingConnection(qintptr socketDescriptor);
    void slotRead();
};