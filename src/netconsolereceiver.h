#ifndef NETCONSOLERECEIVER_H
#define NETCONSOLERECEIVER_H

#include <QTcpSocket>
#include <cstdint>

class NetConsoleReceiver : public QObject
{
    Q_OBJECT
public:
    static const uint16_t PORT = 2122;

    explicit NetConsoleReceiver(QObject *parent = 0);

signals:
    void line(QString str);
    void error(QString error);

public slots:
    void start();

private:
    QTcpSocket* socket;
    QByteArray buffer;

private slots:
    void readFromConsoleSocket();
    void onError(QAbstractSocket::SocketError);
};

#endif // NETCONSOLERECEIVER_H
