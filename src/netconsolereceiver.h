#ifndef NETCONSOLERECEIVER_H
#define NETCONSOLERECEIVER_H

#include <QUdpSocket>
#include <cstdint>

class NetConsoleReceiver : public QObject
{
    Q_OBJECT
public:
    static const uint16_t NETCONSOLE_PORT = 6666;

    explicit NetConsoleReceiver(QObject *parent = 0);

signals:
    void line(QString str);
    void error(QString error);

public slots:
    void start();

private:
    QUdpSocket* socket;
    QByteArray buffer;

private slots:
    void readFromConsoleSocket();
    void onError(QAbstractSocket::SocketError);
};

#endif // NETCONSOLERECEIVER_H
