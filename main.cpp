#include <QtGui/QApplication>
#include "mainwindow.h"
#include "map.h"
#include <QtGui>
#include <QtCore>
#include <QTranslator>

int main(int argc, char *argv[])
{

    //QApplication a(argc, argv);


//    QTranslator translator;
//    translator.load("log73_ru.qm", ".");
//    a.installTranslator(&translator);
//    //qApp->installTranslator(&translator);

//    QTranslator qtTranslator;
//    qtTranslator.load("qt_ru.qm", ".");
//    a.installTranslator(&qtTranslator);

  QSettings* settings = new QSettings(QDir::currentPath() + "/my_config_file.ini", QSettings::IniFormat);

    QString lang = settings->value("Lang").toString();

    if (lang == "RU")
    {
        QApplication a(argc, argv);

        QApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins");

        QTranslator translator;
        translator.load("log73_ru.qm", ".");
        a.installTranslator(&translator);
        //qApp->installTranslator(&translator);

        QTranslator qtTranslator;
        qtTranslator.load("qt_ru.qm", ".");
        a.installTranslator(&qtTranslator);

        MainWindow w;
        w.show();

        return a.exec();
    }
     if (lang == "EN")
    {
        QApplication a(argc, argv);

        QApplication::addLibraryPath(QCoreApplication::applicationDirPath() + "/plugins");

        QTranslator translator;
        translator.load("log73_ru.qm", ".");
        a.removeTranslator(&translator);
        //qApp->installTranslator(&translator);


        QTranslator qtTranslator;
        qtTranslator.load("qt_ru.qm", ".");
        a.removeTranslator(&qtTranslator);


//        QTranslator qtTranslator;
//        qtTranslator.load("qt_uk.qm", ".");
//        a.installTranslator(&qtTranslator);



        MainWindow w;
        w.show();

        return a.exec();
    }






}


