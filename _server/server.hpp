#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server : public QTcpServer
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    Server();
    void Start();
    void Stop();
    QTcpSocket *socket;
    QString text() const;
    void setText(const QString &text);

private:
    QVector<QTcpSocket*> sockets;
    QByteArray Data;
    void sendToClient(const QString str);
    bool parseMessage(QString message, int& inPort);
    int m_port;
    QString m_text;
    quint16 nextBlockSize;

signals:
    void textChanged();

public slots:
    void onSubmitClk(const QString message);
    void incomingConnection(qintptr socketDescriptor);
    void slotRead();
};