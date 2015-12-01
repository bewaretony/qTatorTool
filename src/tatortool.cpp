#include "tatortool.h"
#include "ui_tatortool.h"

#include <QDebug>

TatorTool::TatorTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TatorTool)
{
    ui->setupUi(this);

    this->statusLabel = new QLabel(this);
    statusListening();
    ui->statusBar->addPermanentWidget(statusLabel, 1);

//    for (int i = 0; i < 1000; i++) {
//        this->addDummyData();
//    }
//    lastTimestamp = 0;
//    this->timer = new QTimer(this);

    this->netConsole = new NetConsoleReceiver(this);
    netConsole->start();

    connect(netConsole, SIGNAL(line(QString)), this, SLOT(handleLine(QString)));
    connect(netConsole, SIGNAL(error(QString)), this, SLOT(statusError(QString)));
//    connect(timer, SIGNAL(timeout()), this, SLOT(addDummyData()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

//    timer->start(500);
}

TatorTool::~TatorTool()
{
    delete ui;
}

void TatorTool::handleLine(QString str) {
    ui->logTable->handleLine(str);
    ui->console->append(str);
}

void TatorTool::addDummyData() {
    lastTimestamp += ((double) qrand()) / RAND_MAX;
    LogType logType = LogType::Unknown;
    switch (qrand() % 6) {
    case 0: logType = LogType::Error; break;
    case 1: logType = LogType::Warn; break;
    case 2: logType = LogType::Info; break;
    case 3: logType = LogType::Data; break;
    case 4: logType = LogType::Start; break;
    }

    this->ui->logTable->model()->append(LogItem(lastTimestamp, logType, "Robot", "Hello, World"));
}


void TatorTool::statusListening() {
    this->statusLabel->setText(tr("Listening..."));
}

void TatorTool::statusError(QString error) {
    this->statusLabel->setText(tr("Error: %1").arg(error));
}
