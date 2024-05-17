#include "server.hpp"
#include <iostream>
#include <QDataStream>

Server::Server() : m_port(7300)
{
    try
    { 
        if(this->listen(QHostAddress::Any, m_port))
        {
            qDebug() << "Server listening on port 7300";
        } 
        else 
        {
            qDebug() << "Error listening";
        }
       
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    nextBlockSize = 0;
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    sockets.push_back(socket);
    qDebug() << "New client connected!" << socketDescriptor;
}

void Server::slotRead() {
    socket = (QTcpSocket*)sender();
//   QByteArray data = socket->readAll();
//   qDebug() << "Received: " << data;
//   sendToClient();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);
    if(in.status() == QDataStream::Ok)
    {
        // qDebug() << "Ok";
        // QString str;
        // in >> str;
        // sendToClient(str);
        // setText(str);
        for(;;)
        {
            if(nextBlockSize == 0)
            {
                if(socket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if(socket->bytesAvailable() < nextBlockSize)
            {
                break;
            }
            QString str;
            in >> str;
            nextBlockSize = 0;
            qDebug() << "received - " << str;
            sendToClient(str);
            setText(str);
            break;
        }
    }
}

void Server::sendToClient(const QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(Data.size()-sizeof(quint16));
    for(int i = 0; i < sockets.size(); i++){
        sockets[i]->write(Data);
    }  
}

bool Server::parseMessage(QString message, int& intPort)
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

void Server::onSubmitClk(const QString message)
{
    qDebug() << "onSubmitClk() - " << message;
    int newPort;
    if(parseMessage(message, newPort)) {
        m_port = newPort;
    }
    sendToClient(message);
} 

QString Server::text() const
{
    return m_text;
}

void Server::setText(const QString &text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged();
}