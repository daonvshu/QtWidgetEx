#include "WidgetExTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetExTest w;
    w.show();
    return a.exec();
}
