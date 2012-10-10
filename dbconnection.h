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
    void showAllDBrecords();



    void closeDatabase();



private:
    void populateDatabase();


};

#endif // DBCONNECTION_H
