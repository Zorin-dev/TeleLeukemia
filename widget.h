#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QListWidgetItem>

#include "mygraphicsobject.h"
#include "cellparams.h"

#include <cmath>


#include <QImage>

#include "dialog.h"
#include "propdialog.h"


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void setPathToPdlg(QString path);


private slots:
    void PressEvent();

    void on_pushButton_clicked();//Загрузка изображения в список

    void on_listWidget_itemClicked(QListWidgetItem *item);//Выбор изображения из списка

    void on_pushButton_3_clicked();//Зум +

    void on_pushButton_4_clicked();//Зум -

    void on_pushButton_5_clicked();//HSV

    void on_pushButton_6_clicked();//Бинаризация

    void on_pushButton_2_clicked();//Очистить список

    void on_pushButton_7_clicked();//Эрозия

    void on_pushButton_8_clicked();//Дилатация

    void on_pushButton_9_clicked();//Извлечение изображения

    void on_pushButton_10_clicked();//Сохранение области

    void on_pushButton_11_clicked();//Форма с гистограммами

    void binarisationRed1(int porog);//Бинаризация по R1

    void binarisationRed2(int porog);//Бинаризация по R2

    void binarisationHue1(int porog);//Бинаризация по H1

    void binarisationHue2(int porog);//Бинаризация по H2

    void binarisationGreen1(int porog);//Бинаризация по G1

    void binarisationGreen2(int porog);//Бинаризация по G2

    void binarisationSaturation1(int porog);//Бинаризация по S1

    void binarisationSaturation2(int porog);//Бинаризация по S2

    void binarisationBlue1(int porog);//Бинаризация по B1

    void binarisationBlue2(int porog);//Бинаризация по B2

    void binarisationValue1(int porog);//Бинаризация по V1

    void binarisationValue2(int porog);//Бинаризация по V2

    void on_pushButton_12_clicked();//Автомат

    //void on_lineEdit_2_textChanged(const QString &arg1);//W

   // void on_lineEdit_3_textChanged(const QString &arg1);//H

    void on_pushButton_13_clicked();

  //  bool eventFilter(QObject *target, QEvent *event);

    QImage bibary (QImage src, int porog);


    void clear ();


    void on_pushButton_14_clicked();

    void on_RGB_B_clicked();

    void on_RGB_G_clicked();

    void on_RGB_R_clicked();

    void on_HSV_V_clicked();


    void on_HSV_S_clicked();

    void on_HSV_H_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_extractForAllButton_clicked();

    void on_cellsClassEdit_editingFinished();

private:
    QString imgName;

    int index;
    int next;
    Ui::Widget *ui;

    QGraphicsScene sc;
    MyGraphicsItem *my;

    QImage dilat;

    QString pFiles;
    QString pFile;

    Dialog *dlg;
    Dialog* dlg1;
    PropDialog* pdlg;

    CellParams* cp;

    QImage dst;
    QImage src;

    double mu_gamma(double c, int f, int mu)
    {
        return exp(-c*abs(f-mu));
    }
    
    


};

#endif // WIDGET_H
