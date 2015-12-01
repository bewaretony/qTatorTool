#include "netconsolereceiver.h"

NetConsoleReceiver::NetConsoleReceiver(QObject *parent) : QObject(parent)
{
    this->socket = new QUdpSocket(this);
}

void NetConsoleReceiver::start() {
    socket->bind(QHostAddress::Any, NETCONSOLE_PORT);
    buffer.clear();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readFromConsoleSocket()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
}

void NetConsoleReceiver::readFromConsoleSocket() {
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());

        socket->readDatagram(datagram.data(), datagram.size());
        buffer.append(datagram);
    }
    QList<QByteArray> parts = buffer.split('\n');
    for (int i = 0; i < parts.length() - 1; i++) {
        emit line(QString(parts[i]));
    }
    buffer = parts.last();
}

void NetConsoleReceiver::onError(QAbstractSocket::SocketError) {
    emit error(socket->errorString());
}
