#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map.h"
#include "about.h"
#include "regions.h"
#include "dbconnection.h"

#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtSql>
#include <QSqlTableModel>

#include <QTime>
#include <QFile>
#include <QtCore>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{



    ui->setupUi(this);

    MainWindow::LastLangReadAndApply();

    MainWindow::refreshtable(); //write data from DB when app starts

    reglament turN;
    turN.tur();

    /*
    //show all data from DB for Debug usage
    dbconnection showalldbrec;
    showalldbrec.showAllDBrecords();
    */

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myTimerSlot()));
    timer->start(2000);

    //initialize reglament settings from ini file when app starts
    reglament settings;
    settings.settings();
    settings.settingsRead();

    if (ui->lineEdit_2->text()=="")
        ui->lineEdit_2->setText("1");

    QString currentPath =(QDir::currentPath());
    QString logfile = currentPath.append("/logfile.txt");

    QFile file(logfile);

//initialize txn begin
    dbconnection count;
    int i = count.getCountOfRows();
    ++i;
    QString TxNo = "";
    TxNo.append(QString("%1").arg(i));
    qDebug() << TxNo << "TxNo";
    ui->lineEdit_2->setText(TxNo);
//initialize txn end

      if( !file.exists() )
      {QMessageBox::StandardButton reply;
;

      }
else
      {
      QString file = logfile;

      if (!file.isEmpty())
      {

              QFile sFile(file);
              if(sFile.open(QFile::ReadOnly | QFile::Text))
                {
                  mFilename = file;
                  QTextStream in(&sFile);
                  QString text = in.readAll();
                  sFile.close();
                  //ui->textEdit->setPlainText(text);
                }


               // int i = MainWindow::showscore();

              dbconnection count;
              int i = count.getCountOfRows();

              ++i;

              QString TxNo = "";
              TxNo.append(QString("%1").arg(i));
              qDebug() << TxNo << "TxNo";
               ui->lineEdit_2->setText(TxNo);
      }
      }

    ui->label_callsign->setVisible(false);
    ui->label_txn->setVisible(false);
    ui->label_rxn->setVisible(false);
    ui->label_region->setVisible(false);
    ui->label_qsy->setVisible(false);
    ui->label_6->setVisible(false);





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_write()
{


    ui->label_callsign->setVisible(false);
    ui->label_txn->setVisible(false);
    ui->label_rxn->setVisible(false);
    ui->label_region->setVisible(false);
    ui->label_qsy->setVisible(false);

 QString CALLSIGN = ui->lineEdit->text();


 CALLSIGN = CALLSIGN.trimmed();

 QString RAION = (ui->lineEdit_4->text());
 RAION = RAION.toUpper();

     if (!MainWindow::isThereAnyQSOinThisTur(CALLSIGN))
  {
      //Create QPalette here and set its Color and Color Role
          QPalette *palette = new QPalette();
          palette->setColor(QPalette::Base,Qt::white);
          ui->lineEdit->setPalette(*palette);

          //Create QPalette here and set its Color and Color Role
          //QPalette *palette = new QPalette();
          palette->setColor(QPalette::Base,Qt::white);
          ui->lineEdit_4->setPalette(*palette);
  }

         if ((ui->lineEdit->text()) == "")
 {
     ui->label_callsign->setVisible(true);
     ui->label_qsy->setVisible(false);
     ui->label_callsign->setAlignment(Qt::AlignCenter);
     //ui->label_5->setText(tr(" CALLSIGN "));
     ui->lineEdit->setFocus();
 }
 else if ((ui->lineEdit_2->text()) == "")
 {
     ui->label_txn->setVisible(true);
     ui->label_txn->setAlignment(Qt::AlignCenter);
     //ui->label_txn->setText(" Tx No ");
     ui->lineEdit_2->setFocus();
 }
 else if ((ui->lineEdit_3->text()) == "")
 {
     ui->label_rxn->setVisible(true);
     ui->label_rxn->setAlignment(Qt::AlignCenter);
     //ui->label_rxn->setText(" Rx No ");
     ui->lineEdit_3->setFocus();
 }
else if ((ui->lineEdit_4->text()) == "")
 {

     ui->label_region->setVisible(true);
     ui->label_region->setAlignment(Qt::AlignCenter);
     //ui->label_region->setText(tr(" Region "));
     ui->lineEdit_4->setFocus();
 }
else if(!MainWindow::IsThereSuchRegion(RAION))
         {



             QMessageBox::StandardButton reply;
             QString lang = MainWindow::curlangGet();
             QString title;
             QString question;

                 if (lang == "RU")
                 {
                     title = title.fromUtf8("Внимание!");
                     question = question.fromUtf8("Не существующий регион! Открыть форму добавления региона?");
                 }

                 if (lang == "EN")
                 {
                     title = tr("Attention!");
                     question = tr("Therer is no such region! Whould you like to open regions form?");
                 }

             reply = QMessageBox::warning(this, title,
                                           question,
                                           QMessageBox::Yes | QMessageBox::No );
             if (reply == QMessageBox::Yes)
             {
                 MainWindow::on_actionRegions_triggered();
             }
             else
             {
                 ui->lineEdit_4->setFocus();
             }



         }

 else
    {

    ui->label_6->setVisible(true);
    ui->label_6->setAlignment(Qt::AlignCenter);
    ui->label_6->setText("73!");

    QTime time = QTime::currentTime();
    QString timeString = time.toString("hh:mm");

    QString CALLSIGN = (ui->lineEdit->text());

    MainWindow::sameCALLSIGN = CALLSIGN;

    CALLSIGN = CALLSIGN.toUpper();        // str == "TEXT"


    QString RAION = (ui->lineEdit_4->text());
    RAION = RAION.toUpper();

    QString NumPeredstr = (ui->lineEdit_2->text());

    bool result;

    int NumPered = NumPeredstr.toInt(&result, 10);

    int NumPeredNext = NumPered+1;

    QString NumPeredNextStr = "";

    NumPeredNextStr.append(QString("%1").arg(NumPeredNext));

    ui->lineEdit_2->QLineEdit::clear();
    ui->lineEdit_2->QLineEdit::insert(NumPeredNextStr);

    QString Str0 = "";
    QString Str1 = "0";
    QString Str2 = "00";



    QString NumPeredStr;


    if ((NumPered < 10) && (NumPered > 0))
    {
        Str2.append(QString("%1").arg(NumPered));
        NumPeredStr=(Str2);
    }
    else if ((NumPered < 100) && (NumPered > 9))
    {
        Str1.append(QString("%1").arg(NumPered));
        NumPeredStr=Str1;
    }
    else if (NumPered > 99)
    {
        Str0.append(QString("%1").arg(NumPered));
        NumPeredStr=Str0;
    }


    QString poluchStr0 = "";
    QString poluchStr1 = "0";
    QString poluchStr2 = "00";



    QString NumPoluchStr = (ui->lineEdit_3->text());

//    bool result;

    int NumPoluch = NumPoluchStr.toInt(&result, 10);


    if ((NumPoluch < 10) && (NumPoluch > 0))
    {
        poluchStr2.append(QString("%1").arg(NumPoluch));
        NumPoluchStr=(poluchStr2);
    }
    else if ((NumPoluch < 100) && (NumPoluch > 9))
    {
        poluchStr1.append(QString("%1").arg(NumPoluch));
        NumPoluchStr=poluchStr1;
    }
    else if (NumPoluch > 99)
    {
        poluchStr0.append(QString("%1").arg(NumPoluch));
        NumPoluchStr=poluchStr0;
    }

    QString line;
    line = timeString + "\t\t" + CALLSIGN + "\t" +"\t"+ NumPeredStr + "\t" +"\t"+ NumPoluchStr + "\t"+"\t" + RAION;
    //ui->textEdit->append(line);

ui->textEdit->ensureCursorVisible();


QString callsign = CALLSIGN;
QString region = RAION;

QString timestamp = timeString;
QString txn = NumPeredStr;
QString rxn = NumPoluchStr;

reglament turN;
int tur = turN.tur();


dbconnection aaaa;
aaaa.addCallsign( callsign, region );
dbconnection bbbb;
bbbb.addContest( timestamp, callsign, txn, rxn, region, tur );


QString lastline;
dbconnection gll;

lastline = gll.getLastLine();

//ui->textEdit->append(lastline);










int row = ui->tableWidget->rowCount(); // current row count
ui->tableWidget->setRowCount(row+1); // add one row


//QString timestamp1 = timestamp;

QTableWidgetItem* timestamp1 = new QTableWidgetItem(timestamp);
ui->tableWidget->setItem(row, 0, timestamp1);

QTableWidgetItem* callsign1 = new QTableWidgetItem(callsign);
ui->tableWidget->setItem(row, 1, callsign1);

QTableWidgetItem* txn1 = new QTableWidgetItem(txn);
ui->tableWidget->setItem(row, 2, txn1);

QTableWidgetItem* rxn1 = new QTableWidgetItem(rxn);
ui->tableWidget->setItem(row, 3, rxn1);

QTableWidgetItem* region1 = new QTableWidgetItem(region);
ui->tableWidget->setItem(row, 4, region1);

//ui->tableWidget->set
ui->tableWidget->horizontalHeader()->resizeSection(1, 150); // column 1, width 50
//ui->tableWidget->verticalHeader()->resizeSection(2, 150); // row 2, height 15


ui->lineEdit->clear();
ui->lineEdit_3->clear();
ui->lineEdit_4->clear();


ui->lineEdit->setFocus();


         } //else




//MainWindow::on_actionSave_triggered();

//MainWindow::showscore();

ui->textEdit->selectAll();

//MainWindow::on_actionEdit_done_triggered();

QPalette *palette = new QPalette();
palette->setColor(QPalette::Base,Qt::white);
ui->textEdit->setPalette(*palette);




ui->textEdit->setFocusPolicy(Qt::NoFocus);

MainWindow::refreshtable();

}



void MainWindow::on_actionNew_triggered()
{
    QMessageBox::StandardButton reply;
    QString lang = MainWindow::curlangGet();
    QString title;
    QString question;

        if (lang == "RU")
        {
            title = title.fromUtf8("Внимание!");
            question = question.fromUtf8("Удалить все связи из Log73?");
        }

        if (lang == "EN")
        {
            title = tr("Attention!");
            question = tr("Delete all QSO's from Log73?");
        }

//    QEvent LanguageChange = QEvent::LanguageChange;
//    MainWindow::changeEvent(&LanguageChange);



    reply = QMessageBox::warning(this, title,
                                  question,
                                  QMessageBox::Yes | QMessageBox::No );
            if (reply == QMessageBox::Yes)
    {
        MainWindow::emptyAllrec();
    }





}

void MainWindow::on_actionSave_triggered()
{
    QString currentPath =(QDir::currentPath());
    QString logfile = currentPath.append("/logfile.txt");
    QFile sFile(logfile);
    if(sFile.open(QFile::WriteOnly | QFile::Text) )
    {
        QTextStream out(&sFile);
        out << ui-> textEdit->toPlainText();
        sFile.flush();
        sFile.close();
    }
}


void MainWindow::on_actionSave_as_triggered()
{
    MainWindow::exportfromDB();

   QString file = QFileDialog::getSaveFileName(this,(tr("Save log as txt")));
   if (!file.isEmpty())
    {
       mFilename = file;
       QFile sFile(file);
       if(sFile.open(QFile::WriteOnly | QFile::Text) )
       {
           QTextStream out(&sFile);
           out << ui-> textEdit->toPlainText();
           sFile.flush();
           sFile.close();
       }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    MainWindow::backuplog();
    QString file = QFileDialog::getOpenFileName(this,(tr("Open a logfile.txt")));

    if (!file.isEmpty())
    {
            QFile sFile(file);
            if(sFile.open(QFile::ReadOnly | QFile::Text))
            {
                mFilename = file;
                QTextStream in(&sFile);
                QString text = in.readAll();
                sFile.close();
                ui->textEdit->setPlainText(text);
            }
    }
  //  MainWindow::showscore();
}

void MainWindow::retPressed()
{

    QString CALLSIGN = ui->lineEdit->text();

    if (CALLSIGN =="")
        return;

    CALLSIGN = CALLSIGN.trimmed();
    CALLSIGN = CALLSIGN.toUpper();
    ui->lineEdit->setText(CALLSIGN);

    MainWindow::insertRegion();


    QString RAION = (ui->lineEdit_4->text());
    RAION = RAION.toUpper();
    RAION = RAION.trimmed();
    ui->lineEdit_4->setText(RAION);


    if (MainWindow::isThereAnyQSOinThisTur(CALLSIGN))
     {
         ui->label_6->setVisible(false);
         ui->label_qsy->setVisible(true);
         ui->label_callsign->setVisible(false);
         ui->label_qsy->setAlignment(Qt::AlignCenter);
         ui->label_qsy->setText(" QSY  " + CALLSIGN);

    //Create QPalette here and set its Color and Color Role
                 QPalette *palette = new QPalette();
                 palette->setColor(QPalette::Base,Qt::red);
                 ui->lineEdit->setPalette(*palette);
                 ui->lineEdit_4->setText("");

                 ui->lineEdit->setFocus();
     }

//    else


//        MainWindow::on_write();

}

void MainWindow::on_actionShowMap_triggered()
{
    myMap = new map(this);

 // myMap->setAttribute(Qt::WA_WState_WindowOpacitySet);
  //  myMap->setAttribute(Qt::WA_ShowWithoutActivating);
   // myMap->setAttribute (Qt::WA_DontShowOnScreen, false) ;

    myMap->setFocusPolicy(Qt::NoFocus);
    myMap->show();


}

void MainWindow::on_actionAbout_triggered()
{
    myAbout = new about(this);
    myAbout->show();
}

void MainWindow::on_actionHelp_triggered()
{
    myHelp = new help(this);
    myHelp->show();
}

int MainWindow::showscore()
{
   int i = ui->textEdit->document()->blockCount();
    QString kk = "Total score: ";
    kk.append(QString("%1").arg(i));
    //ui->statusBar->showMessage(kk);
    return i;
}


void MainWindow::backuplog()

{
    //Backup logfile

    //MainWindow::showscore();
    QTime time2 = QTime::currentTime();
    QString timeString2 = time2.toString("hhmm");

    QDate date = QDate::currentDate();
    QString dateString = date.toString("yyyyMMdd");

//    QString newName = "logfile.txt";
//    newName = dateString+"-"+timeString2+"-"+newName;
//    QDir logf;
//    logf.rename ( "logfile.txt", newName );


//    dbconnection CloseDB;
//    CloseDB.closeDatabase();
//    CloseDB.closeDatabase();
//    CloseDB.closeDatabase();
//    CloseDB.closeDatabase();
//    CloseDB.closeDatabase();
//    CloseDB.closeDatabase();
//    CloseDB.closeDatabase();
//    CloseDB.closeDatabase();
//    CloseDB.closeDatabase();


//    QString newNameDB = "loggerdatabase.db";
//    newNameDB = dateString+"-"+timeString2+"-"+newNameDB;
//    QDir logDB;
//    logDB.rename ( "loggerdatabase.db", newNameDB );

    dbconnection delrec;
    delrec.deleteRecords();

}

void MainWindow::on_actionEdit_text_triggered()
{


    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::red);
    ui->textEdit->setPalette(*palette);


    ui->textEdit->setFocusPolicy(Qt::ClickFocus);
   // ui->textEdit->installEventFilter(this);

    ui->textEdit->QTextEdit::moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);




}

void MainWindow::on_actionEdit_done_triggered()
{
      //  ui->textEdit->setEnabled(false);
      //  ui->textEdit->focusPolicy.(NoFocus);

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::white);
    ui->textEdit->setPalette(*palette);

    ui->lineEdit->setFocus();
    ui->textEdit->setFocusPolicy(Qt::NoFocus);






   // ui->textEdit->installEventFilter(this);


}

QTime MainWindow::diffr ( const QTime &t1,const QTime &t2 )
{
#define SEC_MS	1000
#define MIN_MS	(SEC_MS * 60)
#define HOUR_MS	(MIN_MS * 60)

        int diff = t2.msecsTo(t1);
        return QTime(diff/HOUR_MS,(diff % HOUR_MS) / MIN_MS, (diff % MIN_MS) / SEC_MS,diff % SEC_MS);

//int QTime::msecsTo ( const QTime & t ) const
}

void MainWindow::on_pushButton_4_clicked()
{
    int row = ui->tableWidget->rowCount(); // current row count
    ui->tableWidget->setRowCount(row+1); // add one row
    // create items in all added cells
    for (int col = 0; col < (ui->tableWidget->columnCount()); ++col)
    {
        //qDebug()<<ui->tableWidget->columnCount();
        //qDebug()<<col;
    QTableWidgetItem* newItem = new QTableWidgetItem("blaa");
    ui->tableWidget->setItem(row, col, newItem);
   }
    //ui->tableWidget->set
    ui->tableWidget->horizontalHeader()->resizeSection(1, 150); // column 1, width 50
    //ui->tableWidget->verticalHeader()->resizeSection(2, 150); // row 2, height 15

}

void MainWindow::myTimerSlot()
{
    QTime time = QTime::currentTime();
    QString timeString = time.toString("hh:mm");

//   qDebug() << "Timer min executed!";

    ui->clock->setText(timeString);


}

void MainWindow::on_actionSetup_triggered()
{
    myReglament = new reglament(this);
    myReglament->show();
}

bool MainWindow::isThereAnyQSOinThisTur(QString CALLSIGN)
{
    reglament turN;
    int tur = turN.tur();

//    QString CALLSIGN = (ui->lineEdit->text());
    CALLSIGN = CALLSIGN.toUpper();

    dbconnection qsoDB;
    bool qso = qsoDB.isThereAnyQSOinThisTur(CALLSIGN, tur);

    //qDebug() << "isThereAnyQSOinThisTur - " << qso;

    qsoDB.delEmptyRecordsFromContest();

    return qso;



}


QString MainWindow::rstrip(const QString& str) {
  int n = str.size() - 1;
  for (; n >= 0; --n) {
    if (!str.at(n).isSpace()) {
      return str.left(n + 1);
    }
  }
  return "";
}


void MainWindow::isQSOforTab()
{



    QString CALLSIGN = ui->lineEdit->text();
    CALLSIGN = CALLSIGN.trimmed();
    CALLSIGN = CALLSIGN.toUpper();
    ui->lineEdit->setText(CALLSIGN);

    MainWindow::insertRegion();

    if (MainWindow::isThereAnyQSOinThisTur(CALLSIGN))
     {
         ui->label_6->setVisible(false);
         ui->label_qsy->setVisible(true);
         ui->label_qsy->setAlignment(Qt::AlignCenter);
         ui->label_qsy->setText(" QSY  " + CALLSIGN);

    //Create QPalette here and set its Color and Color Role
                 QPalette *palette = new QPalette();
                 palette->setColor(QPalette::Base,Qt::red);
                 ui->lineEdit->setPalette(*palette);


                 palette->setColor(QPalette::Base,Qt::white);
                 ui->lineEdit_4->setPalette(*palette);
                 ui->lineEdit->setFocus();
     }

        if (!MainWindow::isThereAnyQSOinThisTur(CALLSIGN))
     {
         //Create QPalette here and set its Color and Color Role
             QPalette *palette = new QPalette();
             palette->setColor(QPalette::Base,Qt::white);
             ui->lineEdit->setPalette(*palette);
             ui->label_callsign->setVisible(false);
             ui->label_txn->setVisible(false);
             ui->label_rxn->setVisible(false);
             ui->label_region->setVisible(false);
             ui->label_qsy->setVisible(false);
             ui->label_6->setVisible(false);
     }
}

void MainWindow::on_otmenaButton_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit->setFocus();

    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::white);

    ui->lineEdit->setPalette(*palette);
    ui->lineEdit_4->setPalette(*palette);

    ui->label_callsign->setVisible(false);
    ui->label_txn->setVisible(false);
    ui->label_rxn->setVisible(false);
    ui->label_region->setVisible(false);
    ui->label_qsy->setVisible(false);
    ui->label_6->setVisible(false);


}


void MainWindow::load_all_records_to_tableWidget()
{

    QString lastline;
    dbconnection gll;

//    lastline = gll.take_certain_record_from_db(2);

    QByteArray qb = lastline.toUtf8();
    char *ch = qb.data();

    char tur = ch [0];
    QString tur2 = QString(tur);





   // QString tur2 = "String";
    //char b[20];
 //   strcpy( ch, tur2.toStdString().c_str());

   //         qDebug() <<tur2;


  //  qDebug() << lastline;
//    qDebug() << ch [0];
//    qDebug() << ch [2];
//    qDebug() << ch [3];
//    qDebug() << ch [4];
//    qDebug() << ch [5];

//    qDebug() << ch [6];
//    qDebug() << ch [7];
//    qDebug() << ch [8];
//    qDebug() << ch [9];
//    qDebug() << ch [10];
//    qDebug() << ch [11];

    int row = ui->tableWidget->rowCount(); // current row count
    ui->tableWidget->setRowCount(row+1); // add one row

      QTableWidgetItem* tur1 = new QTableWidgetItem(tur2);
      ui->tableWidget->setItem(row, 0, tur1);

//    QTableWidgetItem* timestamp1 = new QTableWidgetItem(timestamp);
//    ui->tableWidget->setItem(row, 0, timestamp1);

//    QTableWidgetItem* callsign1 = new QTableWidgetItem(callsign);
//    ui->tableWidget->setItem(row, 1, callsign1);

//    QTableWidgetItem* txn1 = new QTableWidgetItem(txn);
//    ui->tableWidget->setItem(row, 2, txn1);

//    QTableWidgetItem* rxn1 = new QTableWidgetItem(rxn);
//    ui->tableWidget->setItem(row, 3, rxn1);

//    QTableWidgetItem* region1 = new QTableWidgetItem(region);
//    ui->tableWidget->setItem(row, 4, region1);

//    ui->tableWidget->horizontalHeader()->resizeSection(1, 150); // column 1, width 50
//    //ui->tableWidget->verticalHeader()->resizeSection(2, 150); // row 2, height 15




}

 void MainWindow::refreshtable()
{

//model begins


   QSqlDatabase db;
   db = QSqlDatabase::addDatabase("QSQLITE");

   db.setDatabaseName("loggerdatabase.db");
   if( !db.open())
       qFatal("Failed to open database");


    QSqlTableModel *model;

    model = new QSqlTableModel(this);
    model->setTable("contest");

//     model->setRelation( 1, QSqlRelation ( "callsigns", "id", "callsign"));
//     model3->setRelation( 2, QSqlRelation ( "callsigns", "id", "region"));

    model->select();

    //model->removeColumn(0);
    ui->tableView_3->setModel(model);
    ui->tableView_3->hideColumn(0);
    ui->tableView_3->horizontalHeader()->resizeSection(1, 80);
    ui->tableView_3->horizontalHeader()->resizeSection(2, 150);
    ui->tableView_3->horizontalHeader()->resizeSection(3, 60);
    ui->tableView_3->horizontalHeader()->resizeSection(4, 60);
    ui->tableView_3->horizontalHeader()->resizeSection(5, 80);
    ui->tableView_3->horizontalHeader()->resizeSection(6, 40);

    ui->tableView_3->scrollToBottom();

//model eds
}

void MainWindow::exportfromDB()
{


    dbconnection onel;

    ui->textEdit->setPlainText("");

    dbconnection count;
    int n = count.getCountOfRows();

    QString Oneline;

    for (int i = 1; i <= n; i++)
    {


        Oneline = onel.getOneLine(i);

//        if (Oneline =="")
//        break;

        ui->textEdit->append(Oneline);
    }

}


void MainWindow::emptyAllrec()
{
    mFilename = "";
    ui->textEdit->setPlainText("");
    ui->lineEdit->QLineEdit::clear();
    ui->lineEdit_2->QLineEdit::clear();
    ui->lineEdit_3->QLineEdit::clear();
    ui->lineEdit_4->QLineEdit::clear();
    ui->lineEdit_2->QLineEdit::insert("1");

    dbconnection delrec;
    delrec.deleteRecords();

    MainWindow::refreshtable();


}


void MainWindow::on_otmenaButton_2_clicked()
{
    ui->lineEdit_4->setFocus();
    MainWindow::on_write();

}

void MainWindow::insertRegion()
{
    QString CALLSIGN = ui->lineEdit->text();
    CALLSIGN = CALLSIGN.trimmed();
    CALLSIGN.toUpper();

    dbconnection getregion;
    QString iknowregion = getregion.getRegionForCallsign(CALLSIGN);
    if (iknowregion != "")
    {
    ui->lineEdit_4->setText(iknowregion);

    //Create QPalette here and set its Color and Color Role
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::green);
    ui->lineEdit_4->setPalette(*palette);
    }
    else
    {
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Base,Qt::white);
        ui->lineEdit_4->setPalette(*palette);
        ui->lineEdit_4->setText("");
    }
}


void MainWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {

        //question = tr("All records will be deleted!");
       //title = tr(title);
        //title = tr("Attention!");


    } else
        QWidget::changeEvent(event);
}


void MainWindow::on_actionRussian_triggered()
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

    QString CURRENTLANGUAGE = "RU";

    MainWindow::curlangSet(CURRENTLANGUAGE);

    QString message;
    QString title;

    title = title.fromUtf8("Информация");
    message = message.fromUtf8("Закройте программу, и откройте её заново, чтобы применить русский язык");

    QMessageBox::information(this, title,
                             message, QMessageBox::Ok );

}

void MainWindow::on_actionEnglish_triggered()
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

    QString CURRENTLANGUAGE = "EN";

    MainWindow::curlangSet(CURRENTLANGUAGE);

    QMessageBox::information(this, "Information",
                             "Please restart the programm to take effect",
                                               QMessageBox::Ok );

}

void MainWindow::curlangSet(QString lang)
{
    QSettings* settings = new QSettings(QDir::currentPath() + "/my_config_file.ini", QSettings::IniFormat);
    settings->setValue("Lang", lang);
    settings->sync();
}

QString MainWindow::curlangGet()
{

    QSettings* settings = new QSettings(QDir::currentPath() + "/my_config_file.ini", QSettings::IniFormat);



    QString lang = settings->value("Lang").toString();

//    if (lang == "RU")
//    {
//    }
//    if (lang == "EN")
//    {
//    }


        return lang;



}


void MainWindow::LastLangReadAndApply()
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


//        QTranslator qtTranslator;
//        qtTranslator.load("qt_ru.qm", ".");
//        //QLibraryInfo::location(QLibraryInfo::TranslationsPath));
//        QCoreApplication::installTranslator(&qtTranslator);

//        QApplication a(argc, argv);

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

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if(e->key() != Qt::Key_Escape)
        QWidget::keyPressEvent(e);
    else {

        MainWindow::on_otmenaButton_clicked();
                }
}


void MainWindow::on_actionRegions_triggered()
{
    myRegions = new regions(this);
    myRegions->show();

}

bool MainWindow::IsThereSuchRegion(QString region)
{
    dbconnection dbconObj;
    return dbconObj.isThereSuchRegion(region);


}
