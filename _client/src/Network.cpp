#include "Network.hpp"
#include <QDataStream>
#include <QQuickItem>

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
    QString str = "Hello from client!!!";
    //QQuickItem *lineEdit = qobject_cast<QQuickItem*>(engine.rootObjects()[0]->findChild<QObject*>("lineEditObjectName"));
    sendMessage(message);
}

void Network::slotReadyRead()
{

    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_0);
    if(in.status() == QDataStream::Ok){
        // textBrowser->append(str);
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
            // setText(str);
            int port;
            addMessage(str);
            if(parseMessage(str, port))
            {
                qDebug() << "Port received:" << port;
                disconnectFromServer();
                m_port = port;
                connectToServer();
            }
            break;
        }
    }
    else 
    {
        // textBrowser->append(QString("Error reading data from socket"));
    }
    // Data = clientSocket->readAll();
    // textBrowser->append(Data);
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

void Network::addMessage(const QString &message)
{
    qDebug() << "Emitting newMessage signal with message:" << message;
    emit newMessage(message);
}

QString Network::text() const
{
    return m_text;
}

void Network::setText(const QString &text)
{
    QQuickItem *rootItem = qobject_cast<QQuickItem*>(m_engine->rootObjects().first());
    if (rootItem) {
        QMetaObject::invokeMethod(rootItem, "addMessageFromCpp",
                                  Q_ARG(QVariant, QVariant::fromValue(text)));
    }
}