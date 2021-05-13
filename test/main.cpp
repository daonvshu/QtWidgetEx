#include "WidgetExTest.h"
#include <QtWidgets/QApplication>

#include <QSslSocket>

#include <qdebug.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetExTest w;
    w.show();

    qDebug() << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << "OpenSSL support:" << QSslSocket::supportsSsl();

    return a.exec();
}
