#ifndef LOGTABLEMODEL_H
#define LOGTABLEMODEL_H

#include <QObject>
#include <QtGlobal>
#include <QAbstractTableModel>
#include <QList>

#include <logitem.h>

class LogTableModel : public QAbstractTableModel
{
public:
    LogTableModel(QObject *parent = 0);
    ~LogTableModel();

    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;

    const QList<LogItem>& getLogItems() const;
    void append(LogItem logItem);
    void clear();

private:
    QList<LogItem> logItems;
};

#endif // LOGTABLEMODEL_H
