#pragma once
#include <QTcpSocket>
#include <QByteArray>
#include <QObject>

class Network : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
public:
    Network(QObject *parent = nullptr);
    QString text() const;
    void setText(const QString &text);

signals:
    void textChanged();

public slots:
    void onButtonClick();
    void onSubmitBtnClick(QString message);

    void slotReadyRead();

private:
    QTcpSocket *clientSocket;
    QByteArray Data;
    void sendMessage(QString message);
    bool parseMessage(QString message, int& intPort);
    int port;
    QString m_text;
    quint16 nextBlockSize;
};
