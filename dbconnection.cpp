#include "dbconnection.h"
#include <QtSql>
#include <QSqlTableModel>


dbconnection::dbconnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("loggerdatabase.db");
    if( !db.open())
        qFatal("Failed to open database");

    populateDatabase();

}

void dbconnection::populateDatabase()
{
    QSqlQuery qry;

    qry.prepare( "CREATE TABLE IF NOT EXISTS callsigns"
                 "(id INTEGER PRIMARY KEY, callsign VARCHAR(15), region VARCHAR(30))" );
    if (!qry.exec())
        qFatal( "Failed to create table callsigns" );

    qry.prepare( "CREATE TABLE IF NOT EXISTS contest"
                 "(id INTEGER PRIMARY KEY, time DATETIME, callsign VARCHAR(15), txn VARCHAR(4), rxn VARCHAR(4), region VARCHAR(30), tur INTEGER)" );
    if (!qry.exec())
        qFatal( "Failed to create table contest" );



}

void dbconnection::closeDatabase()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("loggerdatabase.db");
    db.close();


}


void dbconnection::addCallsign( QString callsign, QString region )
{
    int id;
    QSqlQuery qry;

    qry.prepare( "SELECT COUNT(*) FROM callsigns");
    qry.exec();
    qry.next();
    id=qry.value(0).toInt() +1;

    qry.prepare( "INSERT INTO callsigns (id, callsign, region) VALUES(:id, :callsign, :region)");
    qry.bindValue( ":id", id);
    qry.bindValue( ":callsign", callsign);
    qry.bindValue( ":region", region);
    qry.exec();
}


void dbconnection::addContest( QString time, QString callsign, QString txn, QString rxn, QString region, int tur )
{
    int id = 0;
    QSqlQuery qry;

    qry.prepare( "SELECT COUNT(*) FROM contest");
    qry.exec();
    qry.next();
    id=qry.value(0).toInt() +1;

    qry.prepare( "INSERT INTO contest (id, time, callsign, txn, rxn, region, tur) VALUES(:id, :time, :callsign, :txn, :rxn, :region, :tur)");
    qry.bindValue( ":id", id);
    qry.bindValue( ":time", time);
    qry.bindValue( ":callsign", callsign);
    qry.bindValue( ":txn", txn);
    qry.bindValue( ":rxn", rxn);
    qry.bindValue( ":region", region);
    qry.bindValue( ":tur", tur);
    qry.exec();
}

QString dbconnection::getLastLine()
{
    QSqlQuery qry;

//    qry.prepare( "SELECT COUNT(*) FROM callsigns join contest");

//    if ( !qry.exec())
//        qFatal("Failed to get records");


    qry.prepare( "SELECT contest.time, callsigns.callsign, contest.txn, contest.rxn, callsigns.region FROM callsigns JOIN contest ON callsigns.id = contest.id");
  //  qry.prepare( "SELECT * FROM contest");

    if ( !qry.exec())
        qFatal("Failed to get records");

    QSqlRecord rec = qry.record();
    int cols = rec.count();
    QString temp;
    for ( int c=0;c<cols;c++ )
       temp+="{"+rec.fieldName(c) + ((c<cols-0)?"}\t":"");
    qDebug() << temp << 111;

    QString lastline;
        while (qry.next())
        {

            lastline = "";
            for( int c=0;c<cols;c++ )
                lastline += qry.value(c).toString() + ((c<cols-1)?"\t\t":"");
            qDebug() << lastline;


        }

return lastline;

}

QString dbconnection::ThereWasQSO(QString callsign)
{
    QString ThereWasQSO;
    QSqlQuery qry;

    qry.prepare( "SELECT callsign FROM callsigns WHERE callsign = :callsign");
    qry.bindValue(":callsign", callsign);

    if ( !qry.exec())
        qFatal("Failed to get records in ThereWasQSO() function");


qry.next();
    ThereWasQSO = qry.value(0).toString();

//return ThereWasQSO;



  return ThereWasQSO;

}

QStringList dbconnection::ThereWasQSOlist(QString callsign)
{
    QStringList ThereWasQSOlist;
    QSqlQuery qry;

    qry.prepare( "SELECT callsign FROM callsigns WHERE callsign = :callsign");
    qry.bindValue(":callsign", callsign);

    if ( !qry.exec())
        qFatal("Failed to get records in ThereWasQSO() function");


while (qry.next())
    ThereWasQSOlist << qry.value(0).toString();

return ThereWasQSOlist;




}

QStringList dbconnection::ThereWasQSOtime(QString callsign)
{
    QStringList ThereWasQSOtime;
    QSqlQuery qry;

   // qry.prepare( "SELECT callsigns.id, contest.id, contest.time, callsigns.callsign FROM callsigns LEFT JOIN contest WHERE callsigns.callsign = :callsign ON callsigns.id = contest.id ");
 //good  qry.prepare( "SELECT callsigns.id, callsigns.callsign FROM callsigns WHERE callsigns.callsign = :callsign ");

 //good       qry.prepare( "SELECT contest.id, callsigns.id, callsigns.callsign FROM contest JOIN callsigns ON contest.id = callsigns.id");
        qry.prepare( "SELECT contest.time FROM contest JOIN callsigns ON contest.id = callsigns.id WHERE callsigns.callsign = :callsign");
        qry.bindValue(":callsign", callsign);

    if ( !qry.exec())
        qFatal("Failed to get records in ThereWasQSOtime() function");

/*

    QSqlRecord rec = qry.record();
    int cols = rec.count();
    QString temp;
    for ( int c=0;c<cols;c++ )
       temp+="{"+rec.fieldName(c) + ((c<cols-0)?"}\t":"");
    qDebug() << temp;
        QString lastline;
        while (qry.next())
        {
            temp = "";
            for( int c=0;c<cols;c++ )
                temp += qry.value(c).toString() + ((c<cols-1)?"\t\t":"");
            qDebug() << temp;
         //   lastline=temp;
        }



//    while (qry.next())
//        ThereWasQSOtime << qry.value(2).toString();

int i=0;
while (qry.next())
    i++;
if (i>0)
{

    QSqlRecord rec = qry.record();
    int cols = rec.count();
    QString temp;
    for ( int c=0;c<cols;c++ )
       temp+="{"+rec.fieldName(c) + ((c<cols-0)?"}\t":"");
    qDebug() << temp;
        QString lastline;
        while (qry.next())
        {
            temp = "";
            for( int c=0;c<cols;c++ )
                temp += qry.value(c).toString() + ((c<cols-1)?"\t\t":"");

            qDebug() << temp;

            ThereWasQSOtime << temp;


         //   lastline=temp;
        }


}*/
    while (qry.next())
    ThereWasQSOtime << qry.value(0).toString();


    return ThereWasQSOtime;


}


bool dbconnection::isThereAnyQSOinThisTur(QString callsign, int tur)
{
    bool qso = false;
    QSqlQuery qry;

        qry.prepare( "SELECT tur FROM contest WHERE callsign = :callsign AND tur = :tur");
        qry.bindValue(":callsign", callsign);
        qry.bindValue(":tur", tur);

    if ( !qry.exec())
        qFatal("Failed to get records in isThereAnyQSOinThisTur() function");

int isThereAnyQSO = 0;
    while (qry.next())
     isThereAnyQSO= qry.value(0).toInt();
   // qDebug() << isThereAnyQSO;

if (isThereAnyQSO >0)
        qso = true;

    return qso;
}


void dbconnection::showAllDBrecords()
{
    QSqlQuery qry;

        qry.prepare( "SELECT * FROM contest" );

    if ( !qry.exec())
        qFatal("Failed to get records in isThereAnyQSOinThisTur() function");




        QSqlRecord rec = qry.record();
        int cols = rec.count();
        QString temp;
        for ( int c=0;c<cols;c++ )
           temp+="{"+rec.fieldName(c) + ((c<cols-0)?"}\t\t":"");
        qDebug() << temp;
            QString lastline;
            while (qry.next())
            {
                temp = "";
                for( int c=0;c<cols;c++ )
                    temp += qry.value(c).toString() + ((c<cols-1)?"\t\t":"");
                qDebug() << temp;
            }

}






QString dbconnection::getOneLine(int id)
{

QSqlQuery qry;



qry.prepare( "SELECT contest.time, contest.callsign, contest.txn, contest.rxn, contest.region from contest");
//  qry.prepare( "SELECT * FROM contest");

if ( !qry.exec())
    qFatal("Failed to get records");

QSqlRecord rec = qry.record();
int cols = rec.count();
QString temp;
for ( int c=0;c<cols;c++ )
   temp+="{"+rec.fieldName(c) + ((c<cols-0)?"}\t":"");
qDebug() << temp << 222;

QString Oneline;
//    while (qry.next())
//    {

//        Oneline = "";
//        for( int c=0;c<cols;c++ )
//            Oneline += qry.value(c).toString() + ((c<cols-1)?"\t\t":"");
//        qDebug() << Oneline;
//    }

    for(int i=0; i<id; i++)
    {
        qry.next();

        Oneline = "";
        for( int c=0;c<cols;c++ )
            Oneline += qry.value(c).toString() + ((c<cols-1)?"\t\t":"");
        qDebug() << Oneline;
    }

Oneline.remove(QRegExp(":"));

return Oneline;

}

int dbconnection::getCountOfRows()
{


QSqlQuery qry;

    qry.prepare( "SELECT COUNT(*) FROM contest");

    if (!qry.exec())
    qFatal("Failed to get records");

    int temp;

    while (qry.next())
        {
        temp = qry.value(0).toInt();
        qDebug() << temp << 555;
        }

    return temp;

}
void dbconnection::deleteRecords()
{

            QSqlQuery qry;
            qry.exec(QString("delete from contest"));

            if (!qry.exec())
            qFatal("Failed to delete records");


}
