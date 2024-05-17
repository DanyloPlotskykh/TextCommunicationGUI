#include "Network.hpp"
#include <QDataStream>
#include <QQuickItem>

Network::Network(QObject *parent) : QObject(parent),
                                    port(7300)
{
    clientSocket = new QTcpSocket(this);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Network::slotReadyRead);
    nextBlockSize = 0;
}

void Network::onButtonClick()
{
    clientSocket->connectToHost("127.0.0.1", port);
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
            int port;
            if(parseMessage(str, port))
            {
                qDebug() << "Port received:" << port;
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

QString Network::text() const
{
    return m_text;
}

void Network::setText(const QString &text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged();
}