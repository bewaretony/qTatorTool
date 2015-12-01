#include "console.h"
#include "ui_console.h"

Console::Console(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Console)
{
    ui->setupUi(this);
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
}

Console::~Console()
{
    delete ui;
}

void Console::append(QString str) {
    ui->consoleText->append(str);
}

void Console::clear() {
    ui->consoleText->clear();
}
