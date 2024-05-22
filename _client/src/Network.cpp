#include "Network.hpp"

#include <QRegularExpression>
#include <QDataStream>
#include <QQuickItem>
#include <QPair>

template <typename T1, typename T2>
QPair<T1, T2> make_pair(const T1& first, const T2& second) {
    return QPair<T1, T2>(first, second);
}

Network::Network(QObject *parent) : QObject(parent),
                                    m_port(7300)
{
    clientSocket = new QTcpSocket(this);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Network::slotReadyRead);
    nextBlockSize = 0;
}

void Network::connectToServer() 
{
    clientSocket->abort();
    clientSocket->connectToHost("127.0.0.1", m_port);
    if (clientSocket->waitForConnected(3000)) {
        qDebug() << "Connected to server on port" << m_port;
    } else {
        emit conncetToServerFailed();
        qDebug() << "Failed to connect to server";
    }
}

void Network::disconnectFromServer()
{
    clientSocket->disconnectFromHost();
}

void Network::onButtonClick()
{
    connectToServer();
}

void Network::onSubmitBtnClick(QString message)
{
    sendMessage(message);
}

void Network::slotReadyRead()
{

    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_0);
    if(in.status() == QDataStream::Ok){
        for(;;)
        {
            if(nextBlockSize == 0)
            {
                if(clientSocket->bytesAvailable() < 2)
                {
                    break;
                }
                in >> nextBlockSize;
            }
            if(clientSocket->bytesAvailable() < nextBlockSize)
            {
                break;
            }
            QString str;
            in >> str;
            nextBlockSize = 0;
            qDebug() << "received - " << str;
            auto pair = parser(str);
            if(pair.first == "newport-" && pair.second > 1024 && pair.second < 65535)
            {
                qDebug() << "Port received:" << pair.second;
                disconnectFromServer();
                m_port = pair.second;
                connectToServer();
            }
            else if(pair.first == "//delete-")
            {
                deleteMessage(pair.second);
            }
            else
            {
                addMessage(str);
                m_listMessages.append(str);
            }
            break;
        }
    }
    else 
    {
        addMessage(QString("Error reading data from socket"));
    }
}

void Network::sendMessage(QString message) {
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint16(0) << message;
    out.device()->seek(0);
    out << quint16(Data.size()-sizeof(quint16));
    clientSocket->write(Data);    
}

QPair<QString, int> Network::parser(QString message)
{
    QString strNumber;
    message.remove(' ');
    message = message.toLower();
    for (const QChar& c : message) {
        if (c.isDigit()) {
            strNumber.append(c);
        }
    }
    message.remove(QRegExp("\\d"));
    return make_pair(message, strNumber.toInt());
}

void Network::addMessage(const QString &message)
{
    qDebug() << "Emitting newMessage signal with message:" << message;
    emit newMessage(message);
}

bool isAllDigits(const QString &str) {
    QRegularExpression re("^\\d+$");
    return re.match(str).hasMatch();
}

void Network::onChangePortClick(const QString& message)
{
    qDebug() << "log message: " << message;
    if(isAllDigits(message))
    {   
        int intPort = message.toInt();
        if(intPort > 1024 && intPort < 65535)
        {
            sendMessage(QString("newport-") + QString::number(intPort));
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

void Network::onDeleteBtnClick(const int id)
{
    sendMessage(QString("//delete-") + QString::number(id));
}

void Network::deleteMessage(const int id)
{
    m_listMessages.removeAt(id);
    emit deleteQmlMessage(id);
}