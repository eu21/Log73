#include "regions.h"
#include "ui_regions.h"
#include "dbconnection.h"

#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtSql>
#include <QSqlTableModel>


#include <QtCore>



#include <QtGui>

regions::regions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::regions)
{
    ui->setupUi(this);

    regions::refreshtable();

    regions::settingsRead();
    ui->lineEdit->setFocus();


}

regions::~regions()
{
    delete ui;
}


void regions::refreshtable()
{

//model begins


  QSqlDatabase db;
  db = QSqlDatabase::addDatabase("QSQLITE");

  db.setDatabaseName("loggerdatabase.db");
  if( !db.open())
      qFatal("Failed to open database");


   QSqlTableModel *model;

   model = new QSqlTableModel(this);
   model->setTable("regions");


   model->select();

   ui->tableView->setModel(model);
   ui->tableView->hideColumn(0);
//   ui->tableView_3->horizontalHeader()->resizeSection(1, 80);
//   ui->tableView_3->horizontalHeader()->resizeSection(2, 150);
//   ui->tableView_3->horizontalHeader()->resizeSection(3, 60);
//   ui->tableView_3->horizontalHeader()->resizeSection(4, 60);
//   ui->tableView_3->horizontalHeader()->resizeSection(5, 80);
//   ui->tableView_3->horizontalHeader()->resizeSection(6, 40);

   ui->tableView->scrollToBottom();

//model eds
}

void regions::onRetPressed()
{

    QString region = ui->lineEdit->text();
    region = region.toUpper();
    ui->lineEdit->setText(region);




}

void regions::onWrite()
{

QString region = ui->lineEdit->text();
region = region.toUpper();
if (region!="")
{
dbconnection bbbb;
bbbb.addRegion(region);

ui->lineEdit->setText("");

}


}

void regions::on_pushButton_clicked()
{
    QString region = ui->lineEdit->text();
    region = region.toUpper();

    //qDebug() << regions::isThereSuchRegion(region)<< "regions::isThereSuchRegion(region)" ;
    if(!regions::isThereSuchRegion(region))
    {
    regions::onWrite();
    }

    else
    {
        QString title;
        QString question;

        title = title.fromUtf8("Внимание!");
        question = question.fromUtf8("Регион уже был добавлен");


        if(regions::isThereSuchRegion(region))
        {
            QMessageBox::information(this, title,
                               question, QMessageBox::Close );

            //QMessageBox::information( this, "Invalid Data Entered", "You have entered invalid data\n"

        ui->lineEdit->setText("");
        }
    }
    regions::refreshtable();
}

bool regions::isThereSuchRegion(QString region)
 {
    bool isThereSuchRegionBool;

    dbconnection dbconnectionObj;
    if(dbconnectionObj.isThereSuchRegion(region))
    {
    isThereSuchRegionBool = true;
    }
    else
    {
        isThereSuchRegionBool = false;
    }

    dbconnectionObj.delEmptyRecords();

    return isThereSuchRegionBool;
 }

void regions::settingsRead()
{

    QSettings* settings = new QSettings(QDir::currentPath() + "/my_config_file.ini", QSettings::IniFormat);



    QString lang = settings->value("Lang").toString();

    if (lang == "RU")
    {

        //change to russian
        QTranslator translator;
        translator.load("log73_ru.qm", ".");
        QCoreApplication::installTranslator(&translator);
        //qApp->installTranslator(&translator);


        QTranslator qtTranslator;
        qtTranslator.load("qt_ru.qm", ".");
        //QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        QCoreApplication::installTranslator(&qtTranslator);


        ui->retranslateUi(this);

    }
     if (lang == "EN")
    {
        //change to russian
        QTranslator translator;
        translator.load("log73_ru.qm", ".");
        QCoreApplication::removeTranslator(&translator);
        //qApp->installTranslator(&translator);


        QTranslator qtTranslator;
        qtTranslator.load("qt_ru.qm", ".");
        //QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        QCoreApplication::removeTranslator(&qtTranslator);

        ui->retranslateUi(this);

    }

}



