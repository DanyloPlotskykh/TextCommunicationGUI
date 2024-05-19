#pragma once
#include <QTcpSocket>
#include <QByteArray>
#include <QQmlApplicationEngine>
#include <QObject>

class Network : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    explicit Network(QObject *parent = nullptr);
    QString text() const;
    

signals:
    void textChanged();
    void newMessage(const QString& message);

public slots:
    void onButtonClick();
    void onSubmitBtnClick(QString message);
    void setText(const QString &text);
    void slotReadyRead();
    void addMessage(const QString &message);

private:
    QTcpSocket *clientSocket;
    QByteArray Data;
    void connectToServer();
    void disconnectFromServer();
    void sendMessage(QString message);
    bool parseMessage(QString message, int& intPort);
    int m_port;
    QString m_text;
    quint16 nextBlockSize;
    QQmlApplicationEngine *m_engine;
};
