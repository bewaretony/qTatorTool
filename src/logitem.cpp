#include "logitem.h"

#include <QDebug>

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
    case LogType::Debug:
        return "DEBUG";
    case LogType::Trace:
        return "TRACE";
    default:
    case LogType::Unknown:
        return "UNKNOWN";
    }
}

LogType LogItem::logTypeFromString(const QString& str) {
    QString norm = str.trimmed().toUpper();
    if (norm == "ERROR") {
        return LogType::Error;
    } else if (norm == "WARN") {
        return LogType::Warn;
    } else if (norm == "INFO") {
        return LogType::Info;
    } else if (norm == "DEBUG") {
        return LogType::Debug;
    } else if (norm == "TRACE") {
        return LogType::Trace;
    } else {
        return LogType::Unknown;
    }
}

const char* LogItem::PARSE_REGEXP_STR = "^(?<timestamp>[0-9:.]+) \\[(?<thread>.*)\\] (?<type>[A-Z]+) +(?<source>.*) - (?<message>.*)$";

bool LogItem::fromString(const QString& str, LogItem *logItem) {
    QRegularExpression regexp(PARSE_REGEXP_STR, QRegularExpression::CaseInsensitiveOption);

    auto match = regexp.match(str);
    if (!match.hasMatch()) {
        qWarning() << "failed to parse " << str;
        return false;
    }
    double timestamp = match.captured("timestamp").toDouble();
    LogType type = logTypeFromString(match.captured("type"));
    QString source = match.captured("source");
    QString message = match.captured("message");
    *logItem = LogItem(timestamp, type, source, message);
    return true;
}
