#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>
#include "map.h"
#include "regions.h"
#include "about.h"
#include "help.h"
#include "reglament.h"
#include "newdatabaseconfirmation.h"
#include <QTableWidget>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QString rstrip(const QString& str);

//    QString question;
//    QString title;



        void on_write();
        void refreshtable();
        void emptyAllrec();
        void changeEvent(QEvent *event);
        void keyPressEvent(QKeyEvent *e);
        void insertRegion();
        void curlangSet(QString lang);
        QString curlangGet();
        void LastLangReadAndApply();
        bool IsThereSuchRegion(QString region);


public slots:

    void myTimerSlot();
    void isQSOforTab();
    void exportfromDB();


private slots:

    void retPressed();

    void on_actionNew_triggered();

    void on_actionSave_as_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionShowMap_triggered();

    void on_actionAbout_triggered();

    void on_actionHelp_triggered();

    int showscore();

    void backuplog();

    void on_actionEdit_text_triggered();

    void on_actionEdit_done_triggered();

    void on_pushButton_4_clicked();

    QTime diffr ( const QTime &t1,const QTime &t2 );

    void on_actionSetup_triggered();

    bool isThereAnyQSOinThisTur(QString CALLSIGN);

    void on_otmenaButton_clicked();

    void load_all_records_to_tableWidget();


    void on_otmenaButton_2_clicked();

    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();


    void on_actionRegions_triggered();

private:
    Ui::MainWindow *ui;
    QString mFilename;
    QString sameCALLSIGN;
    map *myMap;
    regions *myRegions;
    about *myAbout;
    reglament *myReglament;
    NewDatabaseConfirmation *mynewdatabaseconfirmation;
    help *myHelp;
    QTimer *timer;

    QTableWidget* tableWidget;

};

#endif // MAINWINDOW_H
