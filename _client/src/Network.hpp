#pragma once
#include <QTcpSocket>
#include <QByteArray>
#include <QQmlApplicationEngine>
#include <QObject>
#include <QList>

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
    void deleteQmlMessage(const int id);

public slots:
    void onButtonClick(); // onConnectToServer
    void onSubmitBtnClick(QString message);
    void slotReadyRead();
    void onChangePortClick(const QString& message);
    void onDeleteBtnClick(const int id);

private:
    QTcpSocket *clientSocket; // server
    QByteArray Data;
    int m_port;
    quint16 nextBlockSize;
    QList<QString> m_listMessages;

private:
    void connectToServer();
    void disconnectFromServer();
    void sendMessage(QString message); // const &
    QPair<QString, int> parser(QString message);
    void addMessage(const QString &message);
    void deleteMessage(const int id);

};
