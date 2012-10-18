#ifndef NEWDATABASECONFIRMATION_H
#define NEWDATABASECONFIRMATION_H

#include <QDialog>

namespace Ui {
    class NewDatabaseConfirmation;
}

class NewDatabaseConfirmation : public QDialog
{
    Q_OBJECT

public:
    explicit NewDatabaseConfirmation(QWidget *parent = 0);
    ~NewDatabaseConfirmation();

private slots:
    void on_buttonBox_accepted();


private:
    Ui::NewDatabaseConfirmation *ui;
};

#endif // NEWDATABASECONFIRMATION_H
