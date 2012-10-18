#ifndef REGIONS_H
#define REGIONS_H

#include <QDialog>

namespace Ui {
class regions;
}

class regions : public QDialog
{
    Q_OBJECT
    
public:
    explicit regions(QWidget *parent = 0);
    ~regions();
    
    void refreshtable();

    void onWrite();
    void settingsRead();

private slots:
    void on_pushButton_clicked();
    void onRetPressed();
    bool isThereSuchRegion(QString region);

private:
    Ui::regions *ui;
};

#endif // REGIONS_H
