#include "logtable.h"
#include "ui_logtable.h"

#include <QScrollBar>
#include <QDebug>

LogTableFilterModel::LogTableFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent), m_sourceFilter() {
    setDynamicSortFilter(true);
}

void LogTableFilterModel::setSourceFilter(const QRegularExpression& regexp)
{
    m_sourceFilter = regexp;
    invalidateFilter();
}

void LogTableFilterModel::setSourceFilter(const QString& filterStr) {
    QRegularExpression regexp(filterStr, QRegularExpression::CaseInsensitiveOption);
    regexp.optimize();
    qDebug() << "set source filter to " << filterStr;
    setSourceFilter(regexp);
}

void LogTableFilterModel::setMessageFilter(const QRegularExpression& regexp)
{
    m_messageFilter = regexp;
    invalidateFilter();
}

void LogTableFilterModel::setMessageFilter(const QString& filterStr) {
    QRegularExpression regexp(filterStr, QRegularExpression::CaseInsensitiveOption);
    regexp.optimize();
    qDebug() << "set message filter to " << filterStr;
    setMessageFilter(regexp);
}

bool LogTableFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {
    return filterAcceptsSource(source_row, source_parent) && filterAcceptsMessage(source_row, source_parent);
}

bool LogTableFilterModel::filterAcceptsSource(int source_row, const QModelIndex &source_parent) const {
    if (!sourceFilter().isValid() || sourceFilter().pattern().isEmpty()) {
        return true;
    }

    QModelIndex index = sourceModel()->index(source_row, 2, source_parent);
    QString source = sourceModel()->data(index).toString();
    return sourceFilter().match(source).hasMatch();
}

bool LogTableFilterModel::filterAcceptsMessage(int source_row, const QModelIndex &source_parent) const {
    if (!messageFilter().isValid() || messageFilter().pattern().isEmpty()) {
        return true;
    }

    QModelIndex index = sourceModel()->index(source_row, 3, source_parent);
    QString source = sourceModel()->data(index).toString();
    return messageFilter().match(source).hasMatch();
}

LogTable::LogTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogTable)
{
    ui->setupUi(this);

    this->m_model = new LogTableModel(this);
    this->m_filterModel = new LogTableFilterModel(this);
    m_filterModel->setSourceModel(m_model);

    ui->logTable->setModel(m_filterModel);
    ui->logTable->resizeColumnToContents(0);
    ui->logTable->setColumnWidth(1, 60);
    ui->logTable->setColumnWidth(2, 120);

    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clear()));
    connect(ui->logTable->verticalScrollBar(), SIGNAL(rangeChanged(int,int)), this, SLOT(adjustScrollBar(int,int)));
    connect(ui->sourceFilter, SIGNAL(textChanged(QString)), m_filterModel, SLOT(setSourceFilter(QString)));
    connect(ui->messageFilter, SIGNAL(textChanged(QString)), m_filterModel, SLOT(setMessageFilter(QString)));
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

void LogTable::clear() {
    this->model()->clear();
}

void LogTable::handleLine(QString str) {
    Q_UNUSED(str);
    LogItem item;
    if (LogItem::fromString(str, &item)) {
        append(item);
    }
}

void LogTable::append(LogItem item) {
    this->model()->append(item);
}
