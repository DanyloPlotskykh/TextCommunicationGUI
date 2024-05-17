#include "server.hpp"
#include <iostream>
#include <QDataStream>

Server::Server() : m_port(7300)
{
    Start();
}

void Server::Start()
{
    if (this->isListening()) {
        qDebug() << "Server is already running!";
        return;
    }

    if (!this->listen(QHostAddress::Any, m_port)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started on port" << m_port;
    }
    nextBlockSize = 0;
}

void Server::Stop()
{
    if (this->isListening()) {
        this->close();
        qDebug() << "Server stopped!";
    }
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
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_0);
    if(in.status() == QDataStream::Ok)
    {
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
            int port;
            sendToClient(str);
            setText(str); 
            // if(parseMessage(str, port))
            // {
            //     Stop();
            //     m_port = port;
            //     Start();
            // }
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
    int newPort;
    if(parseMessage(str, newPort))
    {
        qDebug() << "New port: " << newPort;
        Stop();
        m_port = newPort;
        Start();
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