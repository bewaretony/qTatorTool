#ifndef LOGTABLE_H
#define LOGTABLE_H

#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <logtablemodel.h>

namespace Ui {
class LogTable;
}

class LogTable : public QWidget
{
    Q_OBJECT

public:
    explicit LogTable(QWidget *parent = 0);
    ~LogTable();

    LogTableModel* model() { return m_model; }

public slots:
    void clearLog();

private:
    Ui::LogTable *ui;
    QScrollBar *verticalScrollBar;
    LogTableModel *m_model;

private slots:
    void adjustScrollBar(int min, int max);
};

#endif // LOGTABLE_H
