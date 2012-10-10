#ifndef REGLAMENT_H
#define REGLAMENT_H

#include <QDialog>
#include <QTime>

namespace Ui {
class reglament;
}

class reglament : public QDialog
{
    Q_OBJECT
    
public:
    explicit reglament(QWidget *parent = 0);
    int tur();
    void settings();
    void settingsRead();
    void settingsWrite();





    ~reglament();



private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::reglament *ui;
};

#endif // REGLAMENT_H
