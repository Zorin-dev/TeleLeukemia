#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&sc);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::SetImg(QImage &src)
{
    img=&src;
    sc.addPixmap(QPixmap::fromImage(*img));
}
