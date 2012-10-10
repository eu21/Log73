#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <QtCore>
#include <QtGui>


namespace Ui {
    class about;
}

class about : public QDialog
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0);
    ~about();

private slots:

    void on_label_linkActivated(const QString &link);

private:
    Ui::about *ui;
};

#endif // ABOUT_H
