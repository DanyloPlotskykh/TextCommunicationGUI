#include "server.hpp"
#include <iostream>
#include <QDataStream>

Server::Server()
{
    try
    { 
        if(this->listen(QHostAddress::Any, 7300))
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
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    std::cout << "sdfsfd" << std::endl;
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
        qDebug() << "Ok";
        QString str;
        in >> str;
        sendToClient(str);
    }
}

void Server::sendToClient(QString str)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << str;
    for(int i = 0; i < sockets.size(); i++){
        sockets[i]->write(Data);
    }
    socket->write(Data);    
}
