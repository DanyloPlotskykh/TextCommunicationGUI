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

public slots:
    void onButtonClick();
    void onSubmitBtnClick(QString message);
    void slotReadyRead();
    void addMessage(const QString &message);
    void onChangePortClick(const QString& message);

private:
    QTcpSocket *clientSocket;
    QByteArray Data;
    void connectToServer();
    void disconnectFromServer();
    void sendMessage(QString message);
    bool parseMessage(QString message, int& intPort);
    int m_port;
    quint16 nextBlockSize;
};
