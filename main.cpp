#include "tatortool.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TatorTool w;
    w.show();

    return a.exec();
}
