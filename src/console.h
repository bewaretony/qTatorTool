#ifndef CONSOLE_H
#define CONSOLE_H

#include <QWidget>

namespace Ui {
class Console;
}

class Console : public QWidget
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();

public slots:
    void append(QString str);
    void clear();

private:
    Ui::Console *ui;
};

#endif // CONSOLE_H
