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
    QTcpSocket *socket; // unique_ptr // listenSocket

private:
    QVector<QTcpSocket*> sockets;// clients
    QByteArray Data; // shouldn't be member of the class
    int m_port;
    quint16 nextBlockSize;
    QList<QString> m_listMessages;

    //for timer
    std::thread m_timerThread; // strange
    std::atomic<bool> stop_timer;
    std::condition_variable cv;
    std::mutex cv_m; // what covers mutex?
    

private:
    void sendToClient(const QString str); // which client?
    void timer();
    void deleteMessage(const int id);
    QPair<QString, int> parser(QString message);

signals:
    void newMessage(const QString& message);
    void incorrectPort();
    void connectionStatusChanged();
    void conncetToServerFailed();
    void onTimer(const int port); 
    void deleteQmlMessage(const int id); // looks weird

public slots:
    void onSubmitClk(const QString message); // &
    void incomingConnection(qintptr socketDescriptor);
    void slotRead();// onRead
    void startServer();// qinvocable
    void addMessage(const QString &message);
    void onChangePortClick(const QString& message);
    void timerSlot(const int port);// const is extra here
    void onDeleteBtnClick(const int id); 
};