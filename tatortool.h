#ifndef TATORTOOL_H
#define TATORTOOL_H

#include <QMainWindow>
#include <QTimer>
#include <QUdpSocket>
#include <QScrollBar>
#include <QLabel>

#include <logtablemodel.h>

namespace Ui {
class TatorTool;
}

class TatorTool : public QMainWindow
{
    Q_OBJECT

public:
    static const uint16_t NETCONSOLE_PORT = 6666;

    explicit TatorTool(QWidget *parent = 0);
    ~TatorTool();

private:
    void initConsoleSocket();

    Ui::TatorTool *ui;
    QLabel *statusLabel;

    QUdpSocket *consoleSocket;
    QTimer *timer;
    double lastTimestamp;

private slots:
    void readFromConsoleSocket();
    void addDummyData();

    void statusListening();
    void statusError(QAbstractSocket::SocketError);

};

#endif // TATORTOOL_H
