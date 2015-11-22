#include "logtable.h"
#include "ui_logtable.h"

#include <QScrollBar>

LogTable::LogTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogTable)
{
    ui->setupUi(this);

    this->m_model = new LogTableModel(this);
    ui->logTable->setModel(m_model);
    ui->logTable->resizeColumnToContents(0);
    ui->logTable->setColumnWidth(1, 60);
    ui->logTable->resizeColumnToContents(2);

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearLog()));
    connect(ui->logTable->verticalScrollBar(), SIGNAL(rangeChanged(int,int)), this, SLOT(adjustScrollBar(int,int)));
}

LogTable::~LogTable()
{
    delete ui;
}

void LogTable::adjustScrollBar(int min, int max) {
    Q_UNUSED(min);
    if (ui->scrollCheckBox->isChecked()) {
        ui->logTable->verticalScrollBar()->setValue(max);
    }
}

void LogTable::clearLog() {
    this->model()->clear();
}
