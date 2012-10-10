#ifndef MAP_H
#define MAP_H

#include <QDialog>
#include <QtCore>
#include <QtGui>

namespace Ui {
    class map;
}

class map : public QDialog
{
    Q_OBJECT

public:
    explicit map(QWidget *parent = 0);
    ~map();

private slots:

private:
    Ui::map *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsRectItem *rectangle;
    QGraphicsPixmapItem  *pixmap;

};

#endif // MAP_H
