#include <QtGui/QApplication>
#include "mainwindow.h"
#include "map.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins");

    MainWindow w;
    w.show();

    return a.exec();
}

