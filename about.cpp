#include "about.h"
#include "ui_about.h"

about::about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::about)
{

    ui->setupUi(this);

}


about::~about()
{
    delete ui;
}


void about::on_label_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl("http://eu2fm.my1.ru/", QUrl::TolerantMode));
}
