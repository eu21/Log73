#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QObject>

#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QtSql>
#include <QSqlTableModel>

#include <QtDebug>

class dbconnection
{
public:
    dbconnection();
    QStringList ThereWasQSOlist(QString callsign);
    QString ThereWasQSO(QString callsign);
    QStringList ThereWasQSOtime(QString callsign);
    bool isThereAnyQSOinThisTur(QString callsign, int tur);
    QString getLastLine();

    QString getOneLine(int id);

    QString getRegionForCallsign(QString callsign);


    int getCountOfRows();

    QString glob_callsign;
    QString glob_region;
    QString glob_timestamp;
    QString glob_txn;
    QString glob_rxn;
    int glob_tur;

    void deleteRecords();


    void addCallsign(QString callsign, QString region);
    void addContest(QString time, QString callsign, QString txn, QString rxn, QString region, int tur );
    void addRegion( QString region );
    bool isThereSuchRegion(QString region);
    void showAllDBrecords();
    void delEmptyRecordsFromContest();

    void delEmptyRecords();


    void closeDatabase();



private:
    void populateDatabase();


};

#endif // DBCONNECTION_H
