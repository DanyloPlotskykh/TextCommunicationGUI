#include "Network.hpp"
#include <QDataStream>
#include <QQuickItem>

Network::Network(QObject *parent) : QObject(parent),
                                    port(7300)
{
    clientSocket = new QTcpSocket(this);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Network::slotReadyRead);
}

void Network::onButtonClick()
{
    clientSocket->connectToHost("127.0.0.1", port);
}

void Network::onSubmitBtnClick()
{
    QString str = "Hello from client!!!";
    //QQuickItem *lineEdit = qobject_cast<QQuickItem*>(engine.rootObjects()[0]->findChild<QObject*>("lineEditObjectName"));
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

bool Network::parseMessage(QString message, int& intPort)
{
    QString port;
    message.remove(' ');
    message = message.toLower();
    for (const QChar& c : message) {
        if (c.isDigit()) {
            port.append(c);
        }
    }
    message.remove(QRegExp("\\d"));

    if (message == "newport-" && port.size() < 6) {
        bool ok;
        intPort = port.toInt(&ok);
        return ok && (intPort > 1024 && intPort < 65535);
    }
    return false;
}
