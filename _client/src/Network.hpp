#pragma once
#include <QTcpSocket>
#include <QByteArray>
#include <QObject>

class Network : public QObject
{
    Q_OBJECT
public:
    Network(QObject *parent = nullptr);

public slots:
    void onButtonClick();
    void onSubmitBtnClick();

    void slotReadyRead();

private:
    QTcpSocket *clientSocket;
    QByteArray Data;
    void sendMessage(QString message);
    bool parseMessage(QString message, int& intPort);
    int port;
};
