#pragma once
#include <QTcpSocket>
#include <QByteArray>
#include <QQmlApplicationEngine>
#include <QObject>

class Network : public QObject
{
    Q_OBJECT
public:
    explicit Network(QObject *parent = nullptr);
    QString text() const;
    

signals:
    void newMessage(const QString& message);
    void incorrectPort();
    void connectionStatusChanged();
    void conncetToServerFailed();

public slots:
    void onButtonClick();
    void onSubmitBtnClick(QString message);
    void slotReadyRead();
    
    void onChangePortClick(const QString& message);
    

private:
    void addMessage(const QString &message);
    QTcpSocket *clientSocket;
    QByteArray Data;
    void connectToServer();
    void disconnectFromServer();
    void sendMessage(QString message);
    bool parseMessage(QString message, int& intPort);
    int m_port;
    quint16 nextBlockSize;
};
