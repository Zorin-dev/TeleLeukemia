#include "widget.h"
#include "ui_widget.h"


#include <QFileDialog>
#include <QPixmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),index(-1),next(21),my(0),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&sc);

    dlg = new Dialog();
    dlg1 = new Dialog();
    pdlg = new PropDialog();
    cp = NULL;
    ui->cellParamsFileNameLine->setText("all-params");
    ui->cellsClassEdit->setText("-1");
    //pdlg->getButton()->installEventFilter(this);
    QObject::connect(pdlg, SIGNAL(PressSgn()),
               this, SLOT(PressEvent()));
}

Widget::~Widget()
{
    delete ui;
}

///
void Widget::on_pushButton_clicked()//Загрузка изображения в список
{
    ui->listWidget->clear();

    QStringList filePathFewImage = QFileDialog::getOpenFileNames();

        if(filePathFewImage.length() != 0){

    pFiles = (QFileInfo(filePathFewImage[0]).absolutePath());

    foreach (QString file, filePathFewImage)
        ui->listWidget->addItem(QFileInfo(file).fileName());
        }
}

///
#include <QDebug>

void Widget::on_listWidget_itemClicked(QListWidgetItem *item)//Выбор изображения из списка
{
    if(my !=0)
        delete my;
    index = ui->listWidget->row(item);

    my = new MyGraphicsItem(QPixmap((pFiles + "/" +item->text())));
    sc.addItem(my);

    imgName = QString(item->text());
}

///
void Widget::on_pushButton_3_clicked()//Зум +
{
    ui->graphicsView->scale(1.1,1.1);
}

///
void Widget::on_pushButton_4_clicked()//Зум -
{
    ui->graphicsView->scale(1/1.1,1/1.1);
}

///
void Widget::on_pushButton_5_clicked()//HSV
{
    src = my->pixmap().toImage();



    dst = src;

    for (int x = 2 ;x < (src.width()-2) ; ++x)
        for (int y = 2 ; y<(src.height()-2);++y)
        {
            // qDebug()<< ((QColor(src.pixel(x,y)).hue()*100)/255);

            // qDebug()<< ((QColor(src.pixel(x,y)).saturation()));

            int nh = ((QColor(src.pixel(x,y)).hue()*100)/255);//тон
            int ns = ((QColor(src.pixel(x,y)).saturation()));//насыщенность
            int nv = ((QColor(src.pixel(x,y)).value()*100)/255);//яркость

            int rd = (QColor(src.pixel(x,y)).red())*0.299;
            int gr = (QColor(src.pixel(x,y)).green())*0.587;
            int bl = (QColor(src.pixel(x,y)).blue())*0.114;
            int g = rd+gr+bl;

            //dst.setPixel(x,y,qRgb(nh,ns,nv));
            //dst.setPixel(x,y,qRgb(nh,nh,nh));
            dst.setPixel(x,y,qRgb(g,g,g));
            //dst.setPixel(x,y,qRgb(nv,nv,nv));
        }
    my->setPixmap(QPixmap::fromImage(dst));
}

///
//QImage img;
void Widget::on_pushButton_6_clicked()//Бинаризация
{
    // on_pushButton_5_clicked();

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    int porog = ui->lineEdit->text().toInt();

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qRed (src.pixel(x,y))>porog&&  qGreen(src.pixel(x,y))>porog&&  qBlue(src.pixel(x,y))>porog)
            {
                dst.setPixel(x,y, qRgb(255,255,255));
            }
            else
                dst.setPixel(x,y, qRgb(0,0,0));

        }
    my->setPixmap(QPixmap::fromImage(dst));
}

///
void Widget::on_pushButton_2_clicked()//Очистить список
{

}

///
void Widget::on_pushButton_7_clicked()//Эрозия
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);

    for (int x=1; x<src.width()-1; ++x)
        for (int  y=1; y<src.height()-1; ++y)
        {
            for (int i=-1; i <=1; ++i)
                for (int  j=-1; j <= 1; ++j)
                {
                    if(qRed(src.pixel(x,y)) == 0)
                    {
                        dst.setPixel(x+i,y+j,qRgb(0,0,0));//Рост тёмных областей
                    }
                }
        }
    my->setPixmap(QPixmap::fromImage(dst));
}

///
void Widget::on_pushButton_8_clicked()//Дилатация
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);

    //dilat = dst;

    for (int x=1; x<src.width()-1; ++x)
        for (int  y=1; y<src.height()-1; ++y)
        {
            for (int i=-1; i <=1; ++i)
                for (int  j=-1; j <= 1; ++j)
                {
                    if(qRed(src.pixel(x,y)) == 255)
                    {
                        dst.setPixel(x+i,y+j,qRgb(255,255,255));//Рост светлых областей
                    }
                }
        }
    my->setPixmap(QPixmap::fromImage(dst));
}

///
void Widget::on_pushButton_9_clicked()//Извлечение областей
{
    QImage src = my->pixmap().toImage();
    QImage dst;
    dst.load((pFiles + "/" +ui->listWidget->item(index)->text()),"BMP");

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
            if(qRed(src.pixel(x,y)) == 200)//0 или 255 в зависимости от использования предобработки (255 с использованием HSV)
            {
                //                int r = qRed(src.pixel(x,y));
                //                int g = qGreen(src.pixel(x,y));
                //                int b = qBlue(src.pixel(x,y));

                //  dst.setPixel(x,y,src.pixel(x,y));
            }
            else
            {
                dst.setPixel(x,y,qRgb(0,0,0));//цвет фона (чёрный, белый)
            }

    my->setPixmap(QPixmap::fromImage(dst));
}

///
void Widget::on_pushButton_10_clicked()//Сохранение области
{

    // for(int i =0; i<10;++i)
    my->getImage().save("out001.bmp","BMP");//Без цикла будет перезаписываться
}

///
void Widget::on_pushButton_11_clicked()//Вызов формы с гистограммами
{

}

///
void Widget::binarisationRed1(int porog)//Бинаризация по R1
{
    on_listWidget_itemClicked(ui->listWidget->currentItem());

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qRed (src.pixel(x,y))>porog)
            {
                dst.setPixel(x,y, qRgb(255,255,255));
            }
            else
                dst.setPixel(x,y, qRgb(0,0,0));

        }
    my->setPixmap(QPixmap::fromImage(dst));

    qDebug()<<"меня изменили1 "<<porog;

}

///
void Widget::binarisationRed2(int porog)//Бинаризация по R2
{
    /*ОБЩАЯ*/
    on_listWidget_itemClicked(ui->listWidget->currentItem());

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    // int porog = ui->lineEdit->text().toInt();

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qRed (src.pixel(x,y))>porog&&  qGreen(src.pixel(x,y))>porog&&  qBlue(src.pixel(x,y))>porog)
            {
                dst.setPixel(x,y, qRgb(255,255,255));
            }
            else
                dst.setPixel(x,y, qRgb(0,0,0));

        }
    my->setPixmap(QPixmap::fromImage(dst));

    qDebug()<<"меня изменили2 "<<porog;

}

void Widget::binarisationHue1(int porog)//Бинаризация по H1
{

    on_listWidget_itemClicked(ui->listWidget->currentItem());

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if  (((QColor(src.pixel(x,y)).hue()*100)/255)>porog)
            {
                dst.setPixel(x,y, qRgb(255,255,255));
            }
            else
                dst.setPixel(x,y, qRgb(0,0,0));

        }
    my->setPixmap(QPixmap::fromImage(dst));

    qDebug()<<"меня изменили3 "<<porog;
}

void Widget::binarisationHue2(int porog)//Бинаризация по H2
{
    //qDebug()<<"меня изменили4 "<<porog;
}

void Widget::binarisationGreen1(int porog)//Бинаризация по G1//
{

    on_listWidget_itemClicked(ui->listWidget->currentItem());

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qGreen (src.pixel(x,y))>porog)
            {
                dst.setPixel(x,y, qRgb(255,255,255));
            }
            else
                dst.setPixel(x,y, qRgb(0,0,0));

        }
    my->setPixmap(QPixmap::fromImage(dst));

    qDebug()<<"меня изменили5 "<<porog;


}

void Widget::binarisationGreen2(int porog)//Бинаризация по G2
{
    //qDebug()<<"меня изменили6 "<<porog;
}

///
void Widget::binarisationSaturation1(int porog)//Бинаризация по S1
{

    on_listWidget_itemClicked(ui->listWidget->currentItem());

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (QColor(src.pixel(x,y)).saturation()>porog)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));

        }
    my->setPixmap(QPixmap::fromImage(dst));

    qDebug()<<"меня изменили7 "<<porog;
}

///
void Widget::binarisationSaturation2(int porog)//Бинаризация по S2
{
    //qDebug()<<"меня изменили8 "<<porog;
}

///
void Widget::binarisationBlue1(int porog)//Бинаризация по B1
{

    on_listWidget_itemClicked(ui->listWidget->currentItem());

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qBlue (src.pixel(x,y))>porog)
            {
                dst.setPixel(x,y, qRgb(255,255,255));
            }
            else
                dst.setPixel(x,y, qRgb(0,0,0));

        }
    my->setPixmap(QPixmap::fromImage(dst));

    qDebug()<<"меня изменили9 "<<porog;
}

///
void Widget::binarisationBlue2(int porog)//Бинаризация по B2
{
    //qDebug()<<"меня изменили10 "<<porog;
}

///
void Widget::binarisationValue1(int porog)//Бинаризация по V1
{

    on_listWidget_itemClicked(ui->listWidget->currentItem());

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (QColor(src.pixel(x,y)).value()>porog)
            {
                dst.setPixel(x,y, qRgb(255,255,255));
            }
            else
                dst.setPixel(x,y, qRgb(0,0,0));

        }
    my->setPixmap(QPixmap::fromImage(dst));

    qDebug()<<"меня изменили11 "<<porog;
}

///
void Widget::binarisationValue2(int porog)//Бинаризация по V2
{
    //qDebug()<<"меня изменили12 "<<porog;
}

///
void Widget::on_pushButton_12_clicked()//Автомат
{
    if(cp!=NULL)
    delete cp;

    QImage src = my->pixmap().toImage();
    QImage dst(src);
    int hist[255];
    for (int i=0;i<255;i++)
        hist[i]=0;

    int temp[255];
    for (int i=0;i<255;i++)
        temp[i]=0;

    double muobj[255];
    for (int i=0;i<255;i++)
        muobj[i]=0;

    double mubck[255];
    for (int i=0;i<255;i++)
        mubck[i]=0;

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            hist[qGreen(src.pixel(x,y))]++;// RGB-g

        }

    int count=0;
    for (int i=0;i<254;i++)
    {
        temp[i]= hist[i+1]-hist[i];
    }
    int max=0;
    int max1=0;
    int min=0;
    int i=ui->lineEdit_4->text().toInt();
    int wnd=ui->lineEdit_5->text().toInt();
    int min1=0;
    while (max==0)
    {
        for(int j=0;j<10;j++)
        {if (temp[i+j]<0)
                count++;
        }
        if (temp[i]<0&&count>5)
            max=i;
        i++;
        count=0;
    }
    while (min==0)
    {
        for(int j=0;j<wnd;j++)
        {if (temp[i+j]>0)
                count++;
        }
        if (temp[i]>0&&count>wnd/2)
            min=i;
        i++;
        count=0;
    }
    i=0;
    while (min1==0)
    {
        for(int j=0;j<wnd;j++)
        {if (hist[i+j]!=0)
                count++;
        }
        if (hist[i]>0&&count>wnd/2)
            min1=i;
        i++;
        count=0;
    }

    if(ui->radioButton->isChecked())
    {
        for (int x=0; x<src.width(); ++x)
            for (int  y=0; y<src.height(); ++y)
            {
                int colorSum = qGreen(src.pixel(x,y)) + qRed(src.pixel(x,y) + qGreen(src.pixel(x,y)));
                if (colorSum == 255) //если цвет белый, то это фон
                {
                    dst.setPixel(x,y, qRgb(0,0,0));
                }
                else
                    dst.setPixel(x,y, qRgb(255,255,255));
            }
    } else
    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qGreen(src.pixel(x,y))>min)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));

        }


    QImage bin(dst);
   // my->setPixmap(QPixmap::fromImage(dst));
    //dst = my->pixmap().toImage();
    cp = new CellParams(&dst);
    cp->setCriteria(ui->lineEdit_9->text().toInt());
    cp->setCriteria1(ui->lineEdit_2->text().toInt());
    cp->ObjSearchWouR();
    //ui->lineEdit_9->setText(QString::number(cp->getCriteria()));
    ui->label->setText(QString::number(min));
    my->setPixmap(QPixmap::fromImage(dst));
    pdlg->clear();
    pdlg->setProps(cp->getCellProps());
    pdlg->setImage(src);
    pdlg->setDst(dst);
    pdlg->setImgName(imgName);
    dlg1->SetImg(bin);
    dlg->SetImg(src);
   // dlg->show();
   // dlg1->show();
   // pdlg->show();

    ui->lineEdit_8->setText(QString::number(cp->getCNT()));
    //QColor(src.pixel(x,y)).hue()*100)/255)>porog
    //117,5
    //92
    //134,5
    //--
    //89,5
    //135,5
}

/*//
void Widget::on_lineEdit_2_textChanged(const QString &arg1)//W
{
    my->setWidthRect(arg1.toInt());
}

///
void Widget::on_lineEdit_3_textChanged(const QString &arg1)//H
{
    my->setHeightRect(arg1.toInt());
}
*/

//Value (значение цвета) или Brightness — яркость


void Widget::on_pushButton_13_clicked()//Расчёт параметров
{
    int param0=0;//
    // int param1=0;
    // int param2=0;

    QImage src = my->pixmap().toImage();
    QImage dst(src);

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qRed (src.pixel(x,y))!=0)//Площадь
            {
                ++param0=0;;
            }

            //Яркость максимум
            //  if (max > qRed(x,y), max = qRed(x,y));
            //            if (max > qRed(src.pixel(x,y)))
            //            {
            //                    max=qRed(src.pixel(x,y));
            //                            //++param1;
            //            }


        }
    qDebug()<<"S"<<param0;

    ui->label->setText(QString::number(param0));//вывод значения

    my->setPixmap(QPixmap::fromImage(dst));
}

QImage Widget::bibary(QImage src,int porog)
{
    QImage dst(src);

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qRed (src.pixel(x,y))>porog&&  qGreen(src.pixel(x,y))>porog&&  qBlue(src.pixel(x,y))>porog)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));


        }
    return dst;
}

void Widget::clear()
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);

    qint32 nHeight = src.height()-1;
    qint32 nWidth = src.width()-1;

    for (int x=1; x<nWidth; ++x)

        for (int  y=1; y<nHeight; ++y)
        {
            if((qRed(src.pixel(x-1,y-1)) != qRed(src.pixel(x,y))) && (qRed(src.pixel(x-1,y)) != qRed(src.pixel(x,y))) &&

                    (qRed(src.pixel(x-1,y+1)) != qRed(src.pixel(x,y)))&& (qRed(src.pixel(x,y-1)) != qRed(src.pixel(x,y))) &&

                    (qRed(src.pixel(x,y+1)) != qRed(src.pixel(x,y))) && (qRed(src.pixel(x+1,y-1)) != qRed(src.pixel(x,y)))&&

                    (qRed(src.pixel(x+1,y)) != qRed(src.pixel(x,y))) && (qRed(src.pixel(x+1,y+1)) != qRed(src.pixel(x,y)))  )
            {
                dst.setPixel(x,y,qRgb(255,255,255));
            }
            else
            {
                // dst.setPixel(x,y,qRgb(0,0,0));



            }
        }
    my->setPixmap(QPixmap::fromImage(dst));


}

void Widget::on_pushButton_14_clicked()
{
    // clear();


    int cImage = ui->listWidget->count()-1;

    // qDebug()<<cImage;

    QVector<QImage> vQImg(ui->listWidget->count());

    for (int  i=0; i<= cImage; ++i)
    {
        vQImg[i].load((pFiles + "/" +ui->listWidget->item(i)->text()),"BMP");
    }

    //    for (int  i=0; i<= cImage; ++i)
    //    {
    //        vQImg[i].save(QString::number(i)+".bmp","BMP");
    //    }

    QImage dst(vQImg[0]);

    dst.fill(Qt::black);

    qint32 nHeight = dst.height();
    qint32 nWidth = dst.width();

    qDebug() <<nHeight;
    qDebug() <<nWidth;

    for (int x = 0; x < nWidth; ++x)
        for (int  y = 0; y < nHeight; ++y)

        {
            int r = (qRed(vQImg[0].pixel(x,y)) | qRed(vQImg[1].pixel(x,y)) | qRed(vQImg[2].pixel(x,y)) |
                    qRed(vQImg[3].pixel(x,y)) | qRed(vQImg[4].pixel(x,y)) /*| qRed(vQImg[5].pixel(x,y))*/);

            int g = (qGreen(vQImg[0].pixel(x,y)) | qGreen(vQImg[1].pixel(x,y)) | qGreen(vQImg[2].pixel(x,y)) |
                    qGreen(vQImg[3].pixel(x,y)) | qGreen(vQImg[4].pixel(x,y)) /*| qGreen(vQImg[5].pixel(x,y))*/);

            int b = (qBlue(vQImg[0].pixel(x,y)) | qBlue(vQImg[1].pixel(x,y)) | qBlue(vQImg[2].pixel(x,y)) |
                    qBlue(vQImg[3].pixel(x,y)) | qBlue(vQImg[4].pixel(x,y)) /*| qBlue(vQImg[5].pixel(x,y))*/);

            dst.setPixel(x,y,qRgb(r,g,b));
        }

    // dst.save("dst.bmp","BMP");
    my->setPixmap(QPixmap::fromImage(dst));
}

void Widget::on_RGB_B_clicked()
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);
    int hist[255];
    for (int i=0;i<255;i++)
        hist[i]=0;

    int temp[255];
    for (int i=0;i<255;i++)
        temp[i]=0;

    double muobj[255];
    for (int i=0;i<255;i++)
        muobj[i]=0;

    double mubck[255];
    for (int i=0;i<255;i++)
        mubck[i]=0;


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            hist[qBlue(src.pixel(x,y))]++;// RGB-b

            // ++hist[QColor(src.pixel(x,y)).value()]; //HSV-V
            //   ++hist[QColor(src.pixel(x,y)).saturation()]; //HSV-S
            // ++hist[((QColor(src.pixel(x,y)).hue()*100)/255)]; //HSV-S
            //            ++G[0][qRed(img.pixel(x,y))];
            //            ++G[1][qGreen(img.pixel(x,y))];
            //            ++G[2][qBlue(img.pixel(x,y))];
            //            ++G[3][((QColor(img.pixel(x,y)).hue()*100)/255)];
            //            ++G[4][QColor(img.pixel(x,y)).saturation()];
            //            ++G[5][QColor(img.pixel(x,y)).value()];

        }



    int count=0;
    for (int i=0;i<254;i++)
    {
        temp[i]= hist[i+1]-hist[i];
    }
    int max=0;
    int max1=0;
    int min=0;
    int i=ui->lineEdit_4->text().toInt();
    int wnd=ui->lineEdit_5->text().toInt();
    int min1=0;
    while (max==0)
    {
        for(int j=0;j<10;j++)
        {if (temp[i+j]<0)
                count++;
        }
        if (temp[i]<0&&count>5)
            max=i;
        i++;
        count=0;
    }
    while (min==0)
    {
        for(int j=0;j<wnd;j++)
        {if (temp[i+j]>0)
                count++;
        }
        if (temp[i]>0&&count>wnd/2)
            min=i;
        i++;
        count=0;
    }
    i=0;
    while (min1==0)
    {
        for(int j=0;j<wnd;j++)
        {if (hist[i+j]!=0)
                count++;
        }
        if (hist[i]>0&&count>wnd/2)
            min1=i;
        i++;
        count=0;
    }


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qBlue(src.pixel(x,y))>min)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));

        }
    my->setPixmap(QPixmap::fromImage(dst));
    ui->label->setText(QString::number(min));

    dst.save("RGB_B.bmp","BMP");
}
/*
QImage src = my->pixmap().toImage();
QImage dst(src);
int hist[255];
for (int i=0;i<255;i++)
    hist[i]=0;

int temp[255];
for (int i=0;i<255;i++)
    temp[i]=0;

double muobj[255];
for (int i=0;i<255;i++)
    muobj[i]=0;

double mubck[255];
for (int i=0;i<255;i++)
    mubck[i]=0;


for (int x=0; x<src.width(); ++x)
    for (int  y=0; y<src.height(); ++y)
    {
        //hist[qGreen(src.pixel(x,y))]++;// RGB-b

        // ++hist[QColor(src.pixel(x,y)).value()]; //HSV-V
         ++hist[QColor(src.pixel(x,y)).saturation()]; //HSV-S
       // ++hist[((QColor(src.pixel(x,y)).hue()*100)/255)]; //HSV-S
        //            ++G[0][qRed(img.pixel(x,y))];
        //            ++G[1][qGreen(img.pixel(x,y))];
        //            ++G[2][qBlue(img.pixel(x,y))];
        //            ++G[3][((QColor(img.pixel(x,y)).hue()*100)/255)];
        //            ++G[4][QColor(img.pixel(x,y)).saturation()];
        //            ++G[5][QColor(img.pixel(x,y)).value()];

    }

//int max5 = *max_element(hist, hist+255);
//for(int x=0; x<256;++x)
//    qDebug()<<x<<"="<<hist[x];



// for(int x=0; x<256;++x)
//    hist[x] = hist[x]/max5;

// hist[0]=0; //добавил Поляков Е.В.


int count=0;
for (int i=0;i<254;i++)
{
    temp[i]= hist[i+1]-hist[i];
}
int max=0;
int max1=0;
int min=0;
int i=ui->lineEdit_4->text().toInt();
int wnd=ui->lineEdit_5->text().toInt();
int min1=0;
while (max==0)
{
    for(int j=0;j<10;j++)
    {if (temp[i+j]<0)
            count++;
    }
    if (temp[i]<0&&count>5)
        max=i;
    i++;
    count=0;
}
while (min==0)
{
    for(int j=0;j<wnd;j++)
    {if (temp[i+j]>0)
            count++;
    }
    if (temp[i]>0&&count>wnd/2)
        min=i;
    i++;
    count=0;
}
i=0;
while (min1==0)
{
    for(int j=0;j<wnd;j++)
    {if (hist[i+j]!=0)
            count++;
    }
    if (hist[i]>0&&count>wnd/2)
        min1=i;
    i++;
    count=0;
}
/*   while (max1==0)
    {
    for(int j=0;j<wnd;j++)
        {if (hist[i+j]==0)
            count++;
        }
        if (hist[i]>wnd/2)
            min1=i;
        i++;
        count==0;
    }
int t=min;
int mu0=0;
int mu1=0;
int a=0;
int b=0;
     for(int i=0; i<t;i++)
     {
         a+=hist[i]*i;
         b+=hist[i];
      }
       mu0=a/b;
a=0;
b=0;
     for(int i=t; i<255;i++)
     {
         a+=hist[i]*i;
         b+=hist[i];
     }
      mu1=a/b;
double c= 1/(max1-min1);
double diver[][]
    this->mu_gamma()
// int porog = ui->lineEdit->text().toInt();

for (int x=0; x<src.width(); ++x)
    for (int  y=0; y<src.height(); ++y)
    {
        if (QColor(src.pixel(x,y)).saturation()>min)
               // (qGreen(src.pixel(x,y))>min)//&&
                /*QColor(src.pixel(x,y)).saturation()>90&& QColor(src.pixel(x,y)).value()>135)
        {
            dst.setPixel(x,y, qRgb(255,255,255));
        }
        else
            dst.setPixel(x,y, qRgb(0,0,0));

    }
my->setPixmap(QPixmap::fromImage(dst));
ui->label->setText(QString::number(min));*/

void Widget::on_RGB_G_clicked()
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);
    int hist[255];
    for (int i=0;i<255;i++)
        hist[i]=0;

    int temp[255];
    for (int i=0;i<255;i++)
        temp[i]=0;

    double muobj[255];
    for (int i=0;i<255;i++)
        muobj[i]=0;

    double mubck[255];
    for (int i=0;i<255;i++)
        mubck[i]=0;


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            hist[qGreen(src.pixel(x,y))]++;// RGB-b

            // ++hist[QColor(src.pixel(x,y)).value()]; //HSV-V
            //   ++hist[QColor(src.pixel(x,y)).saturation()]; //HSV-S
            // ++hist[((QColor(src.pixel(x,y)).hue()*100)/255)]; //HSV-S
            //            ++G[0][qRed(img.pixel(x,y))];
            //            ++G[1][qGreen(img.pixel(x,y))];
            //            ++G[2][qBlue(img.pixel(x,y))];
            //            ++G[3][((QColor(img.pixel(x,y)).hue()*100)/255)];
            //            ++G[4][QColor(img.pixel(x,y)).saturation()];
            //            ++G[5][QColor(img.pixel(x,y)).value()];

        }



    int count=0;
    for (int i=0;i<254;i++)
    {
        temp[i]= hist[i+1]-hist[i];
    }
    int max=0;
    int max1=0;
    int min=0;
    int i=ui->lineEdit_4->text().toInt();
    int wnd=ui->lineEdit_5->text().toInt();
    int min1=0;
    while (max==0)
    {
        for(int j=0;j<10;j++)
        {if (temp[i+j]<0)
                count++;
        }
        if (temp[i]<0&&count>5)
            max=i;
        i++;
        count=0;
    }
    while (min==0)
    {
        for(int j=0;j<wnd;j++)
        {if (temp[i+j]>0)
                count++;
        }
        if (temp[i]>0&&count>wnd/2)
            min=i;
        i++;
        count=0;
    }
    i=0;
    while (min1==0)
    {
        for(int j=0;j<wnd;j++)
        {if (hist[i+j]!=0)
                count++;
        }
        if (hist[i]>0&&count>wnd/2)
            min1=i;
        i++;
        count=0;
    }


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qGreen(src.pixel(x,y))>min)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));

        }
    my->setPixmap(QPixmap::fromImage(dst));
    ui->label->setText(QString::number(min));
    dst.save("RGB_G.bmp","BMP");
}

void Widget::on_RGB_R_clicked()
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);
    int hist[255];
    for (int i=0;i<255;i++)
        hist[i]=0;

    int temp[255];
    for (int i=0;i<255;i++)
        temp[i]=0;

    double muobj[255];
    for (int i=0;i<255;i++)
        muobj[i]=0;

    double mubck[255];
    for (int i=0;i<255;i++)
        mubck[i]=0;


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            hist[qRed(src.pixel(x,y))]++;// RGB-b

            // ++hist[QColor(src.pixel(x,y)).value()]; //HSV-V
            //   ++hist[QColor(src.pixel(x,y)).saturation()]; //HSV-S
            // ++hist[((QColor(src.pixel(x,y)).hue()*100)/255)]; //HSV-S
            //            ++G[0][qRed(img.pixel(x,y))];
            //            ++G[1][qGreen(img.pixel(x,y))];
            //            ++G[2][qBlue(img.pixel(x,y))];
            //            ++G[3][((QColor(img.pixel(x,y)).hue()*100)/255)];
            //            ++G[4][QColor(img.pixel(x,y)).saturation()];
            //            ++G[5][QColor(img.pixel(x,y)).value()];

        }



    int count=0;
    for (int i=0;i<254;i++)
    {
        temp[i]= hist[i+1]-hist[i];
    }
    int max=0;
    int max1=0;
    int min=0;
    int i=ui->lineEdit_4->text().toInt();
    int wnd=ui->lineEdit_5->text().toInt();
    int min1=0;
    while (max==0)
    {
        for(int j=0;j<10;j++)
        {if (temp[i+j]<0)
                count++;
        }
        if (temp[i]<0&&count>5)
            max=i;
        i++;
        count=0;
    }
    while (min==0)
    {
        for(int j=0;j<wnd;j++)
        {if (temp[i+j]>0)
                count++;
        }
        if (temp[i]>0&&count>wnd/2)
            min=i;
        i++;
        count=0;
    }
    i=0;
    while (min1==0)
    {
        for(int j=0;j<wnd;j++)
        {if (hist[i+j]!=0)
                count++;
        }
        if (hist[i]>0&&count>wnd/2)
            min1=i;
        i++;
        count=0;
    }


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (qRed(src.pixel(x,y))>min)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));

        }
    my->setPixmap(QPixmap::fromImage(dst));
    ui->label->setText(QString::number(min));
    dst.save("RGB_R.bmp","BMP");
}

void Widget::on_HSV_V_clicked()
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);
    int hist[255];
    for (int i=0;i<255;i++)
        hist[i]=0;

    int temp[255];
    for (int i=0;i<255;i++)
        temp[i]=0;

    double muobj[255];
    for (int i=0;i<255;i++)
        muobj[i]=0;

    double mubck[255];
    for (int i=0;i<255;i++)
        mubck[i]=0;


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            //hist[qGreen(src.pixel(x,y))]++;// RGB-b

            ++hist[QColor(src.pixel(x,y)).value()]; //HSV-V
            //  ++hist[QColor(src.pixel(x,y)).saturation()]; //HSV-S
            // ++hist[((QColor(src.pixel(x,y)).hue()*100)/255)]; //HSV-S
            //            ++G[0][qRed(img.pixel(x,y))];
            //            ++G[1][qGreen(img.pixel(x,y))];
            //            ++G[2][qBlue(img.pixel(x,y))];
            //            ++G[3][((QColor(img.pixel(x,y)).hue()*100)/255)];
            //            ++G[4][QColor(img.pixel(x,y)).saturation()];
            //            ++G[5][QColor(img.pixel(x,y)).value()];

        }


    int count=0;
    for (int i=0;i<254;i++)
    {
        temp[i]= hist[i+1]-hist[i];
    }
    int max=0;
    int max1=0;
    int min=0;
    int i=ui->lineEdit_4->text().toInt();
    int wnd=ui->lineEdit_5->text().toInt();
    int min1=0;
    while (max==0)
    {
        for(int j=0;j<10;j++)
        {if (temp[i+j]<0)
                count++;
        }
        if (temp[i]<0&&count>5)
            max=i;
        i++;
        count=0;
    }
    while (min==0)
    {
        for(int j=0;j<wnd;j++)
        {if (temp[i+j]>0)
                count++;
        }
        if (temp[i]>0&&count>wnd/2)
            min=i;
        i++;
        count=0;
    }
    i=0;
    while (min1==0)
    {
        for(int j=0;j<wnd;j++)
        {if (hist[i+j]!=0)
                count++;
        }
        if (hist[i]>0&&count>wnd/2)
            min1=i;
        i++;
        count=0;
    }

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (QColor(src.pixel(x,y)).value()>min)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));

        }
    my->setPixmap(QPixmap::fromImage(dst));
    ui->label->setText(QString::number(min));

    dst.save("HSV_V.bmp","BMP");


}

void Widget::on_HSV_S_clicked()
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);
    int hist[255];
    for (int i=0;i<255;i++)
        hist[i]=0;

    int temp[255];
    for (int i=0;i<255;i++)
        temp[i]=0;

    double muobj[255];
    for (int i=0;i<255;i++)
        muobj[i]=0;

    double mubck[255];
    for (int i=0;i<255;i++)
        mubck[i]=0;


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            //hist[qGreen(src.pixel(x,y))]++;// RGB-b

            //  ++hist[QColor(src.pixel(x,y)).value()]; //HSV-V
            ++hist[QColor(src.pixel(x,y)).saturation()]; //HSV-S
            // ++hist[((QColor(src.pixel(x,y)).hue()*100)/255)]; //HSV-S
            //            ++G[0][qRed(img.pixel(x,y))];
            //            ++G[1][qGreen(img.pixel(x,y))];
            //            ++G[2][qBlue(img.pixel(x,y))];
            //            ++G[3][((QColor(img.pixel(x,y)).hue()*100)/255)];
            //            ++G[4][QColor(img.pixel(x,y)).saturation()];
            //            ++G[5][QColor(img.pixel(x,y)).value()];

        }


    int count=0;
    for (int i=0;i<254;i++)
    {
        temp[i]= hist[i+1]-hist[i];
    }
    int max=0;
    int max1=0;
    int min=0;
    int i=ui->lineEdit_4->text().toInt();
    int wnd=ui->lineEdit_5->text().toInt();
    int min1=0;
    while (max==0)
    {
        for(int j=0;j<10;j++)
        {if (temp[i+j]<0)
                count++;
        }
        if (temp[i]<0&&count>5)
            max=i;
        i++;
        count=0;
    }
    while (min==0)
    {
        for(int j=0;j<wnd;j++)
        {if (temp[i+j]>0)
                count++;
        }
        if (temp[i]>0&&count>wnd/2)
            min=i;
        i++;
        count=0;
    }
    i=0;
    while (min1==0)
    {
        for(int j=0;j<wnd;j++)
        {if (hist[i+j]!=0)
                count++;
        }
        if (hist[i]>0&&count>wnd/2)
            min1=i;
        i++;
        count=0;
    }

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (QColor(src.pixel(x,y)).saturation()<min)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));

        }
    my->setPixmap(QPixmap::fromImage(dst));
    ui->label->setText(QString::number(min));

    dst.save("HSV_S.bmp","BMP");
}

void Widget::on_HSV_H_clicked()
{
    QImage src = my->pixmap().toImage();
    QImage dst(src);
    int hist[255];
    for (int i=0;i<255;i++)
        hist[i]=0;

    int temp[255];
    for (int i=0;i<255;i++)
        temp[i]=0;

    double muobj[255];
    for (int i=0;i<255;i++)
        muobj[i]=0;

    double mubck[255];
    for (int i=0;i<255;i++)
        mubck[i]=0;


    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            //hist[qGreen(src.pixel(x,y))]++;// RGB-b

            //  ++hist[QColor(src.pixel(x,y)).value()]; //HSV-V
            //   ++hist[QColor(src.pixel(x,y)).saturation()]; //HSV-S
            ++hist[((QColor(src.pixel(x,y)).hue()*100)/255)]; //HSV-H
            //            ++G[0][qRed(img.pixel(x,y))];
            //            ++G[1][qGreen(img.pixel(x,y))];
            //            ++G[2][qBlue(img.pixel(x,y))];
            //            ++G[3][((QColor(img.pixel(x,y)).hue()*100)/255)];
            //            ++G[4][QColor(img.pixel(x,y)).saturation()];
            //            ++G[5][QColor(img.pixel(x,y)).value()];

        }


    int count=0;
    for (int i=0;i<254;i++)
    {
        temp[i]= hist[i+1]-hist[i];
    }
    int max=0;
    int max1=0;
    int min=0;
    int i=ui->lineEdit_4->text().toInt();
    int wnd=ui->lineEdit_5->text().toInt();
    int min1=0;
    while (max==0)
    {
        for(int j=0;j<10;j++)
        {if (temp[i+j]<0)
                count++;
        }
        if (temp[i]<0&&count>5)
            max=i;
        i++;
        count=0;
    }
    while (min==0)
    {
        for(int j=0;j<wnd;j++)
        {if (temp[i+j]>0)
                count++;
        }
        if (temp[i]>0&&count>wnd/2)
            min=i;
        i++;
        count=0;
    }
    i=0;
    while (min1==0)
    {
        for(int j=0;j<wnd;j++)
        {if (hist[i+j]!=0)
                count++;
        }
        if (hist[i]>0&&count>wnd/2)
            min1=i;
        i++;
        count=0;
    }

    for (int x=0; x<src.width(); ++x)
        for (int  y=0; y<src.height(); ++y)
        {
            if (((QColor(src.pixel(x,y)).hue()*100)/255)<min)
            {
                dst.setPixel(x,y, qRgb(0,0,0));
            }
            else
                dst.setPixel(x,y, qRgb(255,255,255));

        }
    my->setPixmap(QPixmap::fromImage(dst));
    ui->label->setText(QString::number(min));

    dst.save("HSV_H.bmp","BMP");
}

void Widget::on_pushButton_16_clicked()
{

}

void Widget::on_pushButton_17_clicked()
{
    for (int all = 155; all < ui->listWidget->count() ;++all)
    {
        on_listWidget_itemClicked(ui->listWidget->item(all));

        on_RGB_G_clicked();

        on_pushButton_2_clicked();

        on_pushButton_16_clicked();

    }

}

void Widget::setPathToPdlg(QString path){
    pdlg->SetPath(path);
}

void Widget::on_pushButton_18_clicked()
{
    // myfill::black_white(my->pixmap().toImage());


    for (int all = 0; all < ui->listWidget->count() ;++all)
    {
        on_listWidget_itemClicked(ui->listWidget->item(all));

    }

}

void Widget::on_pushButton_15_clicked()
{

}

void Widget::on_pushButton_19_clicked()
{
    pdlg->show();
}

void Widget::on_pushButton_20_clicked()
{
    dlg->show();
}

void Widget::on_pushButton_21_clicked()
{
    dlg1->show();
}


void Widget::PressEvent()
{
  //  if (target == pdlg->getButton())
  //  { int a = event->type();
   //     if (event->type() == QEvent::User)
            my->setPixmap(QPixmap::fromImage(*(pdlg->getImage())));
           // return true;
   // }
  //  return false;
}

void Widget::on_extractForAllButton_clicked()
{
    int listSize = ui->listWidget->count();
    QString fileName = ui->cellParamsFileNameLine->text();
    this->pdlg->setFileName(fileName);
    for(int i = 0 ; i < listSize; i++){
        if(my !=0)
            delete my;

        QListWidgetItem * item = ui->listWidget->item(i);

        my = new MyGraphicsItem(QPixmap((pFiles + "/" +item->text())));
        sc.addItem(my);

        imgName = QString(item->text());

        on_pushButton_12_clicked();

        this->pdlg->setCellsClass(ui->cellsClassEdit->text().toInt());

        this->pdlg->calculateAndSaveParams();

    }

}

void Widget::on_cellsClassEdit_editingFinished()
{
    this->pdlg->setCellsClass(ui->cellsClassEdit->text().toInt());
}
