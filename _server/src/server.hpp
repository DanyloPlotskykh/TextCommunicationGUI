#pragma once

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>
#include <QList>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    ~Server();
    void Start();
    void Stop();
    QTcpSocket *socket;

private:
    QVector<QTcpSocket*> sockets;
    QByteArray Data;
    int m_port;
    quint16 nextBlockSize;
    QList<QString> m_listMessages;
    //for timer
    std::thread m_timerThread;
    std::atomic<bool> stop_timer;
    std::condition_variable cv;
    std::mutex cv_m;
    

private:
    void sendToClient(const QString str);
    bool parseMessage(QString message, int& inPort);
    void timer();
    bool parseDeleteMessage(QString message, int& index);
    QPair<QString, int> parser(QString message);

signals:
    void newMessage(const QString& message);
    void incorrectPort();
    void connectionStatusChanged();
    void conncetToServerFailed();
    void onTimer(const int port);
    void deleteMessage(const int& index);
    void deleteQmlMessage(const int& index);

public slots:
    void onSubmitClk(const QString message);
    void incomingConnection(qintptr socketDescriptor);
    void slotRead();
    void startServer();
    void addMessage(const QString &message);
    void onChangePortClick(const QString& message);
    void timerSlot(const int port);
    void onDeleteBtnClick(const int& index);
};