#include "map.h"
#include "ui_map.h"
#include <QtCore>
#include <QtGui>


map::map(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::map)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QString currentPath =(QDir::currentPath());

    QString currentmap = currentPath.append("/belmap.gif");

   // currentmap.replace('/','\\');

    ui->label->setText(currentmap);

    scene->addPixmap(QPixmap(currentmap));

}



map::~map()
{
    delete ui;
}


