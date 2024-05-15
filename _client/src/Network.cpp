#include "Network.hpp"
#include <QDataStream>

Network::Network(QObject *parent) : QObject(parent)
{
    clientSocket = new QTcpSocket(this);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Network::slotReadyRead);
}

void Network::onButtonClick()
{
    clientSocket->connectToHost("127.0.0.1", 7300);
}

void Network::onSubmitBtnClick()
{
    QString str = "Hello from client!!!";
    sendMessage(str);
}

void Network::slotReadyRead()
{
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_0);
    if(in.status() == QDataStream::Ok){
        QString str;
        in >> str;
        // textBrowser->append(str);
    }
    else 
    {
        // textBrowser->append(QString("Error reading data from socket"));
    }
    Data = clientSocket->readAll();
    // textBrowser->append(Data);
}

void Network::sendMessage(QString message) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << message;
    clientSocket->write(Data);    
}