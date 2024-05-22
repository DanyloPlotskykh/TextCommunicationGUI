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
    QTcpSocket *clientSocket;
    QByteArray Data;
    int m_port;
    quint16 nextBlockSize;

private:
    void connectToServer();
    void disconnectFromServer();
    void sendMessage(QString message);
    QPair<QString, int> parser(QString message);
    void addMessage(const QString &message);
};
