#ifndef TATORTOOL_H
#define TATORTOOL_H

#include <QMainWindow>
#include <QTimer>
#include <QUdpSocket>
#include <QScrollBar>
#include <QLabel>

#include <logtablemodel.h>
#include <netconsolereceiver.h>

namespace Ui {
class TatorTool;
}

class TatorTool : public QMainWindow
{
    Q_OBJECT

public:
    explicit TatorTool(QWidget *parent = 0);
    ~TatorTool();

private:
    Ui::TatorTool *ui;
    QLabel *statusLabel;

    NetConsoleReceiver *netConsole;
    QTimer *timer;
    double lastTimestamp;

private slots:
    void addDummyData();
    void handleLine(QString str);

    void statusListening();
    void statusError(QString error);

};

#endif // TATORTOOL_H
