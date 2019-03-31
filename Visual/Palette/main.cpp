#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.init(15, 15, 20);
    w.show();

    return a.exec();
}
