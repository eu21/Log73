#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <map.h>
#include <about.h>
#include <QFile>
#include "dbconnection.h"
#include <QTime>

#include <QSqlTableModel>
#include <QTableView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtSql>
#include <QSqlTableModel>

#include <QtCore>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

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
      {
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

    ui->label_5->setVisible(false);
    ui->label_6->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_write()
{

 ui->label_5->setVisible(false);
 ui->label_6->setVisible(false);

 QString CALLSIGN = ui->lineEdit->text();


 CALLSIGN = CALLSIGN.trimmed();

     if (!MainWindow::isThereAnyQSOinThisTur(CALLSIGN))
  {
      //Create QPalette here and set its Color and Color Role
          QPalette *palette = new QPalette();
          palette->setColor(QPalette::Base,Qt::white);
          ui->lineEdit->setPalette(*palette);
  }

         if ((ui->lineEdit->text()) == "")
 {
     ui->label_5->setVisible(true);
     ui->label_5->setAlignment(Qt::AlignCenter);
     ui->label_5->setText(" CALLSIGN ");
     ui->lineEdit->setFocus();
 }
 else if ((ui->lineEdit_2->text()) == "")
 {
     ui->label_5->setVisible(true);
     ui->label_5->setAlignment(Qt::AlignCenter);
     ui->label_5->setText(" Tx No ");
     ui->lineEdit_2->setFocus();
 }
 else if ((ui->lineEdit_3->text()) == "")
 {
     ui->label_5->setVisible(true);
     ui->label_5->setAlignment(Qt::AlignCenter);
     ui->label_5->setText(" Rx No ");
     ui->lineEdit_3->setFocus();
 }
else if ((ui->lineEdit_4->text()) == "")
 {

     ui->label_5->setVisible(true);
     ui->label_5->setAlignment(Qt::AlignCenter);
     ui->label_5->setText(" Region ");
     ui->lineEdit_4->setFocus();
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

//MainWindow::backuplog();

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
  //  MainWindow::showscore();

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

   QString file = QFileDialog::getSaveFileName(this,"Save log as txt");
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
    QString file = QFileDialog::getOpenFileName(this,"Open a logfile.txt");

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

    QString RAION = (ui->lineEdit_4->text());
    RAION = RAION.toUpper();
    RAION = RAION.trimmed();
    ui->lineEdit_4->setText(RAION);


                if ((ui->lineEdit->text()) == MainWindow::sameCALLSIGN)
            {
                ui->label_5->setVisible(true);
                ui->label_6->setVisible(false);
                ui->label_5->setAlignment(Qt::AlignCenter);
                ui->label_5->setText(" Same CALLSIGN ");
                ui->lineEdit->setFocus();
            }

    if (MainWindow::isThereAnyQSOinThisTur(CALLSIGN))
     {
         ui->label_6->setVisible(false);
         ui->label_5->setVisible(true);
         ui->label_5->setAlignment(Qt::AlignCenter);
         ui->label_5->setText(" QSY  " + CALLSIGN);

    //Create QPalette here and set its Color and Color Role
                 QPalette *palette = new QPalette();
                 palette->setColor(QPalette::Base,Qt::red);
                 ui->lineEdit->setPalette(*palette);

                 ui->lineEdit->setFocus();
     }

    else
        MainWindow::on_write();

}

void MainWindow::on_actionShowMap_triggered()
{
    myMap = new map(this);
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
/*
void MainWindow::on_pushButton_2_clicked()
{

        ui->label_5->setVisible(false);
        ui->label_6->setVisible(false);

        if ((ui->lineEdit->text()) == "")
        {
            ui->label_5->setVisible(true);
            ui->label_5->setAlignment(Qt::AlignCenter);
            ui->label_5->setText(" CALLSIGN ");
            ui->lineEdit->setFocus();
        }
        else if ((ui->lineEdit_2->text()) == "")
        {
            ui->label_5->setVisible(true);
            ui->label_5->setAlignment(Qt::AlignCenter);
            ui->label_5->setText(" Tx No ");
            ui->lineEdit_2->setFocus();
        }
        else if ((ui->lineEdit_3->text()) == "")
        {
            ui->label_5->setVisible(true);
            ui->label_5->setAlignment(Qt::AlignCenter);
            ui->label_5->setText(" Rx No ");
            ui->lineEdit_3->setFocus();
        }
       else if ((ui->lineEdit_4->text()) == "")
        {

            ui->label_5->setVisible(true);
            ui->label_5->setAlignment(Qt::AlignCenter);
            ui->label_5->setText(" Region ");
            ui->lineEdit_4->setFocus();
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
           line = timeString + "\t" + CALLSIGN + "\t" +"\t"+ NumPeredStr + "\t" +"\t"+ NumPoluchStr + "\t"+"\t" + RAION;

           //ui->textEdit->append(line);



}


}*/









/*
bool MainWindow::on_pushButton_3_clicked()
{
    QString CALLSIGN = (ui->lineEdit->text());
    CALLSIGN = CALLSIGN.toUpper();        // str == "TEXT"

//    dbconnection ThereWasQSOlist;
//    QStringList listofduplicates = ThereWasQSOlist.ThereWasQSOlist(CALLSIGN) ;
//    ui->listWidget->clear();
//    ui->listWidget->addItems(listofduplicates);



        dbconnection ThereWasQSO;
        QString duplicat = ThereWasQSO.ThereWasQSO(CALLSIGN) ;
        ui->lineEdit_5->QLineEdit::clear();
        ui->lineEdit_5->QLineEdit::insert(duplicat);

    dbconnection ThereWasQSOtime;
    QStringList listofduplicatesTime = ThereWasQSOtime.ThereWasQSOtime(CALLSIGN) ;
    ui->listWidget_2->clear();
    ui->listWidget_2->addItems(listofduplicatesTime);
qDebug()<< listofduplicatesTime.count();
    QString lastQSO = listofduplicatesTime.value(listofduplicatesTime.count()-1);
qDebug()<< lastQSO;

QTime t = QTime::fromString(lastQSO,"hh:mm");
qDebug()<<t;

QTime tcur = QTime::currentTime();
QTime difrenc = MainWindow::diffr (tcur,t );

qDebug()<<difrenc;


QString difrencString = difrenc.toString("hh:mm");
ui->lineEdit_6->QLineEdit::clear();
ui->lineEdit_6->QLineEdit::insert(difrencString);
qDebug()<<difrencString;


QTime timeCur = QTime::currentTime();
QString (timeStringCur) = timeCur.toString("hh:mm");

if (timeStringCur == difrencString)
ui->lineEdit_6->QLineEdit::clear();

if (timeCur>t)
    qDebug() << "timeCur > t" ;


QString AllowedMinutesStr = (ui->lineEdit_7->text());

bool result;

int AllowedMinutes = AllowedMinutesStr.toInt(&result, 10);

AllowedMinutes++;

qDebug() << "AllowedMinutes " << AllowedMinutes;


QTime n;
 n = t.addSecs(AllowedMinutes*60);                // t == 14:01:10
bool AllowToGo;

if (timeCur>n)
{
    qDebug() << "timeCur < n. Congrat! AllowedMinutes estim" ;
AllowToGo=true;
 qDebug() << AllowToGo;
}
else
{
    qDebug() << "timeCur > n. AllowedMinutes not estim";
   AllowToGo = false;
 qDebug() << AllowToGo;

}

    return AllowToGo;


}
*/
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

    qDebug() << "isThereAnyQSOinThisTur - " << qso;

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

    if (MainWindow::isThereAnyQSOinThisTur(CALLSIGN))
     {
         ui->label_6->setVisible(false);
         ui->label_5->setVisible(true);
         ui->label_5->setAlignment(Qt::AlignCenter);
         ui->label_5->setText(" QSY  " + CALLSIGN);

    //Create QPalette here and set its Color and Color Role
                 QPalette *palette = new QPalette();
                 palette->setColor(QPalette::Base,Qt::red);
                 ui->lineEdit->setPalette(*palette);
                 ui->lineEdit->setFocus();
     }

        if (!MainWindow::isThereAnyQSOinThisTur(CALLSIGN))
     {
         //Create QPalette here and set its Color and Color Role
             QPalette *palette = new QPalette();
             palette->setColor(QPalette::Base,Qt::white);
             ui->lineEdit->setPalette(*palette);
             ui->label_5->setVisible(false);
             ui->label_6->setVisible(false);
     }
}

void MainWindow::on_otmenaButton_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
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
