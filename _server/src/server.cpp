#include "server.hpp"
#include <QDataStream>
#include <QRegularExpression>
#include <chrono>
#include <random>
#include <QPair>

template <typename T1, typename T2>
QPair<T1, T2> make_pair(const T1& first, const T2& second) {
    return QPair<T1, T2>(first, second);
}

Server::Server() : m_port(7300),
                   stop_timer(false)
{
    connect(this, &Server::onTimer, this, &Server::timerSlot);
    connect(this, &Server::deleteMessage, this, &Server::onDeleteBtnClick);
}   

Server::~Server()
{
    sockets.clear();
}

void Server::timerSlot(const int port)
{ 
    qDebug() << "Timer slot!";
    sendToClient("newport-" + QString::number(port));
}

int generate_random_port() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1024, 65535);
    return dis(gen);
}

void Server::timer()
{
    std::unique_lock<std::mutex> lk(cv_m);
    while (true) {
        if (cv.wait_for(lk, std::chrono::seconds(45), [this]{ return stop_timer.load(); })) {
            qDebug() << "Timer stopped!";
            break;
        } else {
            int port = generate_random_port();
            qDebug() << "Время истекло, выполняем действие!";
            emit onTimer(port);
            break;
        }
    }
    qDebug() << "(after while) Timer thread stopped!";
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
        m_timerThread = std::thread(&Server::timer, this);
    }
    nextBlockSize = 0;
}

void Server::Stop()
{
    if (this->isListening()) {
        this->close();
        qDebug() << "Server stopped!";
    }
    stop_timer = true;
    cv.notify_one();
    m_timerThread.join();
    stop_timer.store(false);
    sockets.clear();
}

void Server::startServer()
{
    Start();
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
            sendToClient(str);
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
    addMessage(str);
    m_listMessages.append(str);
    for(int i = 0; i < sockets.size(); i++){
        sockets[i]->write(Data);
    }
    // auto pair = parser(str);
    // if (pair.first == "newport-" && pair.second < 6 && pair.second > 1024 && pair.second < 65535)) {
        
    // }
    int newPort;
    if(parseMessage(str, newPort))
    {
        qDebug() << "New port: " << newPort;
        Stop();
        m_port = newPort;
        Start();
    }
}

QPair<QString, int> Server::parser(QString message)
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
    return make_pair(message, port.toInt());
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

bool Server::parseDeleteMessage(QString message, int& index)
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
    if(message == "//delete-")
    {
        qDebug() << "Delete message received!";
        // emit deleteMessage(intPort);
        return true;
    }
}

void Server::onSubmitClk(const QString message)
{
    qDebug() << "onSubmitClk() - " << message;
    sendToClient(message);
} 

void Server::addMessage(const QString& message)
{
    emit newMessage(message);
}

bool isAllDigits(const QString &str) {
    QRegularExpression re("^\\d+$");
    return re.match(str).hasMatch();
}

void Server::onChangePortClick(const QString& message)
{
    qDebug() << "log message: " << message;
    if(isAllDigits(message))
    {   
        int intPort = message.toInt();
        if(intPort > 1024 && intPort < 65535)
        {
            sendToClient(QString("newport-") + QString::number(intPort));
            emit connectionStatusChanged();
        }
        else
        {
            emit incorrectPort();
        }
    }
    else
    {
        emit incorrectPort();
    }
}

void Server::onDeleteBtnClick(const int& index)
{
    qDebug() << "Delete button clicked!";
    qDebug() << "index: " << index;
    qDebug() << "size: " << m_listMessages.size();
    if(index >= 0 && index < m_listMessages.size())
    {
        m_listMessages.removeAt(index);
    }
    sendToClient(QString("//delete-")+QString::number(index));
    qDebug() << "size: " << m_listMessages.size();
    emit deleteQmlMessage(index);
}