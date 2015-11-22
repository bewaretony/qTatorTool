#include "logtablemodel.h"

#include <QDebug>
#include <QColor>

LogTableModel::LogTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{

}

LogTableModel::~LogTableModel()
{

}

int LogTableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return logItems.size();
}

int LogTableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 4;
}

QVariant LogTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= logItems.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        auto& logItem = logItems.at(index.row());

        switch (index.column()) {
        case 0:
            return QString("%1").arg(logItem.timestamp(), 0, 'f', 3, '0');
        case 1:
            return logItem.typeString();
        case 2:
            return logItem.source();
        case 3:
            return logItem.message();
        }
    } else if (role == Qt::BackgroundRole) {
        LogType type = logItems.at(index.row()).type();
        switch (type) {
        case LogType::Error:
            return QColor(255, 140, 128);
        case LogType::Warn:
            return QColor(253, 247, 111);
        case LogType::Info:
            return QColor(182, 238, 254);
        case LogType::Start:
            return QColor(153, 255, 102);
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QVariant LogTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return tr("Timestamp");
        case 1:
            return tr("Level");
        case 2:
            return tr("Source");
        case 3:
            return tr("Message");
        }
    }
    return QVariant();
}

Qt::ItemFlags LogTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index);
}

const QList<LogItem>& LogTableModel::getLogItems() const
{
    return logItems;
}

void LogTableModel::append(LogItem logItem) {
    int length = logItems.length();
    beginInsertRows(QModelIndex(), length, length);
    logItems.append(logItem);
    endInsertRows();
}

void LogTableModel::clear() {
    beginResetModel();
    logItems.clear();
    endResetModel();
}
