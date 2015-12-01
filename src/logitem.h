#ifndef LOGITEM_H
#define LOGITEM_H

#include <QString>

#include <logtype.h>
#include <QRegularExpression>


class LogItem
{
public:
    LogItem();

    LogItem(double timestamp, LogType type, const QString& source, const QString& message);

    ~LogItem();

    double timestamp() const;
    LogType type() const;
    QString typeString() const;
    const QString& source() const;
    const QString& message() const;

    static QString logTypeToString(LogType logType);
    static LogType logTypeFromString(const QString& str);
    static bool fromString(const QString& str, LogItem *logItem);

private:
    static const char* PARSE_REGEXP_STR;

    double m_timestamp;
    LogType m_type;
    QString m_source;
    QString m_message;
};

#endif // LOGITEM_H
