#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();
    void Start();
    void Stop();
    QTcpSocket *socket;

private:
    QVector<QTcpSocket*> sockets;
    QByteArray Data;
    void sendToClient(const QString str);
    bool parseMessage(QString message, int& inPort);
    int m_port;
    quint16 nextBlockSize;

signals:
    void newMessage(const QString& message);
    void incorrectPort();
    void connectionStatusChanged();
    void conncetToServerFailed();

public slots:
    void onSubmitClk(const QString message);
    void incomingConnection(qintptr socketDescriptor);
    void slotRead();
    void startServer();
    void addMessage(const QString &message);
    void onChangePortClick(const QString& message);
};