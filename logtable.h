#ifndef LOGTABLE_H
#define LOGTABLE_H

#include <QWidget>
#include <QTableView>
#include <QHBoxLayout>
#include <QSortFilterProxyModel>
#include <QRegularExpression>

#include <logtablemodel.h>

namespace Ui {
class LogTable;
}

class LogTableFilterModel : public QSortFilterProxyModel {
    Q_OBJECT
public:
    LogTableFilterModel(QObject *parent = 0);

    const QRegularExpression& sourceFilter() const { return m_sourceFilter; }
    const QRegularExpression& messageFilter() const { return m_messageFilter; }

public slots:
    void setSourceFilter(const QRegularExpression& regexp);
    void setSourceFilter(const QString& filterStr);
    void setMessageFilter(const QRegularExpression& regexp);
    void setMessageFilter(const QString& filterStr);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    bool filterAcceptsSource(int source_row, const QModelIndex &source_parent) const;
    bool filterAcceptsMessage(int source_row, const QModelIndex &source_parent) const;

    QRegularExpression m_sourceFilter;
    QRegularExpression m_messageFilter;
};

class LogTable : public QWidget
{
    Q_OBJECT

public:
    explicit LogTable(QWidget *parent = 0);
    ~LogTable();

    LogTableModel* model() { return m_model; }

public slots:
    void clear();
    void handleLine(QString str);
    void append(LogItem item);

private:
    Ui::LogTable *ui;
    QScrollBar *verticalScrollBar;
    LogTableModel *m_model;
    LogTableFilterModel *m_filterModel;

private slots:
    void adjustScrollBar(int min, int max);
};

#endif // LOGTABLE_H
