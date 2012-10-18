#include "newdatabaseconfirmation.h"
#include "ui_newdatabaseconfirmation.h"
#include "mainwindow.h"
NewDatabaseConfirmation::NewDatabaseConfirmation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDatabaseConfirmation)
{
    ui->setupUi(this);
}

NewDatabaseConfirmation::~NewDatabaseConfirmation()
{
    delete ui;
}


void NewDatabaseConfirmation::on_buttonBox_accepted()
{
    MainWindow empt;
    empt.emptyAllrec();
    empt.refreshtable();
}


