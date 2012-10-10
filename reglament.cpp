#include "reglament.h"
#include "ui_reglament.h"
#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QTime>

reglament::reglament(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reglament)
{
    ui->setupUi(this);
    reglament::settingsRead();

    //reglament::tur();
}

reglament::~reglament()
{
    delete ui;
}

int reglament::tur()
{
   int tur = 0;

   QTime tcur = QTime::currentTime();

   QTime tur1begin = ui->tur1begin->time();
   QTime tur2begin = ui->tur2begin->time();
   QTime tur3begin = ui->tur3begin->time();
   QTime tur4begin = ui->tur4begin->time();
   QTime tur5begin = ui->tur5begin->time();
   QTime tur6begin = ui->tur6begin->time();
   QTime tur6end = ui->tur6end->time();

    if (tcur > tur1begin)
    {
        qDebug() << "currentTime > tur1begin ";
        tur = 1;
    }
    else
       qDebug() << "currentTime < tur1begin ";

    if (tcur > tur2begin)
    {
        qDebug() << "currentTime > tur2begin ";
        tur = 2;
    }
    else
      qDebug() << "currentTime < tur2begin ";

    if (tcur > tur3begin)
    {
//        qDebug() << "currentTime > tur3begin ";
        tur = 3;
    }
    else
      qDebug() << "currentTime < tur3begin ";

 if (tcur > tur4begin)
 {
       qDebug() << "currentTime > tur4begin ";
     tur = 4;
 }
 else
       qDebug() << "currentTime < tur4begin ";

 if (tcur > tur5begin)
 {
       qDebug() << "currentTime > tur5begin ";
     tur = 5;
 }
 else
       qDebug() << "currentTime < tur5begin ";

 if (tcur > tur6begin)
 {
       qDebug() << "currentTime > tur6begin ";
     tur = 6;
 }
 else
       qDebug() << "currentTime < tur6begin ";

 if (tcur > tur6end)
    {
       qDebug() << "Contest Over!";
       qDebug() << tur6end << " -tur6end";
       qDebug() << tcur<< " -tcur";
       tur = 7;
    }
    else
        qDebug() << "Contest on going.. ";



    qDebug() << "return tur = " << tur ;

   return tur;
}

void reglament::settings()
{

    QSettings* settings = new QSettings(QDir::currentPath() + "/my_config_file.ini", QSettings::IniFormat);
    settings->setValue("Initial", "Initial");

//    QTime tur1beginFromINI = settings.value("tur1begin");
//    ui->tur1begin->setTime(tur1beginFromINI);


    settings->sync();

//    запись:
//    settings.setValue("F",QLocale::c().toString(F, 'f', 6));
//    чтение:
//    C++ (Qt)
//    F = QLocale::c().toFloat(l);

}

void reglament::settingsRead()
{

    QSettings* settings = new QSettings(QDir::currentPath() + "/my_config_file.ini", QSettings::IniFormat);



    QString tur1beginFromINIstring = settings->value("tur1begin").toString();
    QTime tur1beginFromINItime;
    tur1beginFromINItime = tur1beginFromINItime.fromString(tur1beginFromINIstring);
    ui->tur1begin->setTime(tur1beginFromINItime);

    QString tur2beginFromINIstring = settings->value("tur2begin").toString();
    QTime tur2beginFromINItime;
    tur2beginFromINItime = tur2beginFromINItime.fromString(tur2beginFromINIstring);
    ui->tur2begin->setTime(tur2beginFromINItime);

    QString tur3beginFromINIstring = settings->value("tur3begin").toString();
    QTime tur3beginFromINItime;
    tur3beginFromINItime = tur3beginFromINItime.fromString(tur3beginFromINIstring);
    ui->tur3begin->setTime(tur3beginFromINItime);

    QString tur4beginFromINIstring = settings->value("tur4begin").toString();
    QTime tur4beginFromINItime;
    tur4beginFromINItime = tur4beginFromINItime.fromString(tur4beginFromINIstring);
    ui->tur4begin->setTime(tur4beginFromINItime);

    QString tur5beginFromINIstring = settings->value("tur5begin").toString();
    QTime tur5beginFromINItime;
    tur5beginFromINItime = tur5beginFromINItime.fromString(tur5beginFromINIstring);
    ui->tur5begin->setTime(tur5beginFromINItime);

    QString tur6beginFromINIstring = settings->value("tur6begin").toString();
    QTime tur6beginFromINItime;
    tur6beginFromINItime = tur6beginFromINItime.fromString(tur6beginFromINIstring);
    ui->tur6begin->setTime(tur6beginFromINItime);




    QString tur1endFromINIstring = settings->value("tur1end").toString();
    QTime tur1endFromINItime;
    tur1endFromINItime = tur1endFromINItime.fromString(tur1endFromINIstring);
    ui->tur1end->setTime(tur1endFromINItime);

    QString tur2endFromINIstring = settings->value("tur2end").toString();
    QTime tur2endFromINItime;
    tur2endFromINItime = tur2endFromINItime.fromString(tur2endFromINIstring);
    ui->tur2end->setTime(tur2endFromINItime);

    QString tur3endFromINIstring = settings->value("tur3end").toString();
    QTime tur3endFromINItime;
    tur3endFromINItime = tur3endFromINItime.fromString(tur3endFromINIstring);
    ui->tur3end->setTime(tur3endFromINItime);

    QString tur4endFromINIstring = settings->value("tur4end").toString();
    QTime tur4endFromINItime;
    tur4endFromINItime = tur4endFromINItime.fromString(tur4endFromINIstring);
    ui->tur4end->setTime(tur4endFromINItime);

    QString tur5endFromINIstring = settings->value("tur5end").toString();
    QTime tur5endFromINItime;
    tur5endFromINItime = tur5endFromINItime.fromString(tur5endFromINIstring);
    ui->tur5end->setTime(tur5endFromINItime);

    QString tur6endFromINIstring = settings->value("tur6end").toString();
    QTime tur6endFromINItime;
    tur6endFromINItime = tur6endFromINItime.fromString(tur6endFromINIstring);
    ui->tur6end->setTime(tur6endFromINItime);




//    settings->sync();

//    запись:
//    settings.setValue("F",QLocale::c().toString(F, 'f', 6));
//    чтение:
//    C++ (Qt)
//    F = QLocale::c().toFloat(settings.value("F").toString());

}

void reglament::settingsWrite()
{

    QTime tur1begin = ui->tur1begin->time();
    QTime tur2begin = ui->tur2begin->time();
    QTime tur3begin = ui->tur3begin->time();
    QTime tur4begin = ui->tur4begin->time();
    QTime tur5begin = ui->tur5begin->time();
    QTime tur6begin = ui->tur6begin->time();

    QTime tur1end = ui->tur1end->time();
    QTime tur2end = ui->tur2end->time();
    QTime tur3end = ui->tur3end->time();
    QTime tur4end = ui->tur4end->time();
    QTime tur5end = ui->tur5end->time();
    QTime tur6end = ui->tur6end->time();

    QSettings* settings = new QSettings(QDir::currentPath() + "/my_config_file.ini", QSettings::IniFormat);

    settings->setValue("tur1begin", tur1begin);
    settings->setValue("tur2begin", tur2begin);
    settings->setValue("tur3begin", tur3begin);
    settings->setValue("tur4begin", tur4begin);
    settings->setValue("tur5begin", tur5begin);
    settings->setValue("tur6begin", tur6begin);


    settings->setValue("tur1end", tur1end);
    settings->setValue("tur2end", tur2end);
    settings->setValue("tur3end", tur3end);
    settings->setValue("tur4end", tur4end);
    settings->setValue("tur5end", tur5end);
    settings->setValue("tur6end", tur6end);



//    settings->sync();

//    запись:
//    settings.setValue("F",QLocale::c().toString(F, 'f', 6));
//    чтение:
//    C++ (Qt)
//    F = QLocale::c().toFloat(settings.value("F").toString());

}


void reglament::on_buttonBox_accepted()
{
    reglament::settingsWrite();
}

void reglament::on_pushButton_clicked()
{
    reglament::settingsWrite();
}
