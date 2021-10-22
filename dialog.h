#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsScene>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void SetImg(QImage &src);

private:
    Ui::Dialog *ui;
    QGraphicsScene sc;
    QImage *img;
};

#endif // DIALOG_H
