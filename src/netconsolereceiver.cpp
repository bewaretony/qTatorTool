#include "netconsolereceiver.h"

NetConsoleReceiver::NetConsoleReceiver(QObject *parent) : QObject(parent)
{
    this->socket = new QTcpSocket(this);
}

void NetConsoleReceiver::start() {
    buffer.clear();

    connect(socket, SIGNAL(readyRead()), this, SLOT(readFromConsoleSocket()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));
    socket->connectToHost("localhost", PORT);
}

void NetConsoleReceiver::readFromConsoleSocket() {
    while (socket->canReadLine()) {
        char buf[256];
        qint64 len = socket->readLine(buf, sizeof(buf));
        if(len != -1) {
            emit line(QString(buf).trimmed());
        }
    }
}

void NetConsoleReceiver::onError(QAbstractSocket::SocketError) {
    emit error(socket->errorString());
}
