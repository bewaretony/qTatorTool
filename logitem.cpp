#include "logitem.h"

LogItem::LogItem() :
    m_timestamp(0.0), m_type(LogType::Unknown), m_message()
{
}

LogItem::LogItem(double timestamp, LogType type, const QString& source, const QString& message) :
    m_timestamp(timestamp), m_type(type), m_source(source), m_message(message)
{
}

LogItem::~LogItem()
{
}

double LogItem::timestamp() const {
    return m_timestamp;
}

LogType LogItem::type() const {
    return m_type;
}

QString LogItem::typeString() const {
    return logTypeToString(type());
}

const QString& LogItem::source() const {
    return m_source;
}

const QString& LogItem::message() const {
    return m_message;
}

QString LogItem::logTypeToString(LogType logType) {
    switch (logType) {
    case LogType::Error:
        return "ERROR";
    case LogType::Warn:
        return "WARN";
    case LogType::Info:
        return "INFO";
    case LogType::Data:
        return "DATA";
    case LogType::Start:
        return "START";
    default:
    case LogType::Unknown:
        return "UNKNOWN";
    }
}
