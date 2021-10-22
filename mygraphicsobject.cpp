#include "mygraphicsobject.h"

#include <QDebug>

///
void MyGraphicsItem::paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(p,option,widget);

    p->setRenderHint(QPainter::Antialiasing,true);

    p->setPen(QPen(QBrush(QColor(0,255,0)),1,Qt::DashLine));//Цвет контура, толщина, тип линиее
    p->drawRect(twoRect);//Рисуем область(прямоугольник)

    p->setBrush(QBrush(QColor(255,255,255,120)));//Цвет выделенного (фон)
    p->drawRect(selectionRect);

    // p->setPen(QPen(QBrush(QColor(255,0,0)),1,Qt::DashLine));//Настройки правой кнопки
    //p->drawRect(oneRect);//Рисуем область(прямоугольник)

    p->setBrush(Qt::NoBrush);

}

///
QRectF MyGraphicsItem::boundingRect() const
{
    return QGraphicsPixmapItem::boundingRect();
}

///
QImage MyGraphicsItem::getImage()//Копирование области для сохранения
{
    //return this ->pixmap().copy(oneRect).toImage();//Копирование по правой кнопке
    return this ->pixmap().copy(twoRect).toImage();//Копирование по левой кнопке
}

///
void MyGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent *e)//квадратики
{

    /* Закоментировано выделение по нажатию на правую кнопку*/

    //    if (e->button()==Qt::RightButton)//Правая кнопка
    //    {
    //        //  oneRect.setRect(e->pos().x(),e->pos().y(),125,125);//Квадрат - право, низ

    //        oneRect.setCoords(e->pos().x()-125,e->pos().y()-125,e->pos().x()+125,e->pos().y()+125);//Квадрат в центре
    //        // setOneImage(pixmap()->copy(oneRect).toImage());

    //        this->pixmap().copy();

    //        update();
    //        // qDebug()<<e->pos().x()<<e->pos().y();
    //    }

    if (e->button()==Qt::LeftButton)//Правая кнопка
    {
        qDebug()<<"Coordinates:"<<QString::number((e->pos().x()))<<" and "<<QString::number((e->pos().y()));
        point.setX(e->pos().x());
        point.setY(e->pos().y());
        emit MouseClicked();
        //QImage tmp = this->pixmap().toImage();

        //tmp.setPixel(e->pos().x(),e->pos().y(),qRgb(0,0,0));

        //this->setPixmap(QPixmap::fromImage(tmp));
        //update();
    }

    if (e->button()==Qt::RightButton)//Левая кнопка
    {
        //twoRect.setRect(e->pos().x(),e->pos().y(),250,250);//Квадрат - право, низ

        //twoRect.setCoords(e->pos().x()-125,e->pos().y()-125,e->pos().x()+125,e->pos().y()+125);//Квадрат в центре

        // twoRect.setRect(e->pos().x(),e->pos().y(),w,h);//квадрат рисуется из левого угла - прва, низ
        twoRect.setCoords(e->pos().x()-w,e->pos().y()-h,e->pos().x()+w,e->pos().y()+h);//Квадрат рисуется по центру



        //setTwoImage(pixmap()->copy(twoRect).toImage());
        this->pixmap().copy();

        update();

        //qDebug()<<e->pos().x()<<e->pos().y();

        calc();

        //selectionRect.setTopLeft(e->pos());
        //  selectionRect.setBottomRight(e->pos());
    }

    //            if (e->button()==Qt::LeftButton)
    //            {
    //                if (selectionRect.contains(e->pos())) contextMenu.exec(this->mapToGlobal(e->pos()));
    //             }
    //                else
    //             {
    //                selectionStarted=true;
    //                 selectionRect.setTopLeft(e->pos());
    //                 selectionRect.setBottomRight(e->pos());
    //             }
}

///
void MyGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent *e)//отслеживание позиции мыши****НЕ ИСПОЛЬЗУЕТСЯ
{
    //    if (selectionStarted)
    //    {
    //        selectionRect.setBottomRight(e->pos().toPoint());
    //        update();
    //    }
    //    if (selectionStarted)
    //    {
    //        selectionRect.setBottomLeft(e->pos().toPoint());
    //        update();
    //    }


}

///
void MyGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)//проверка отжатия мыши****
{
    Q_UNUSED(e)
    selectionStarted=false;
}

void MyGraphicsItem::calc()
{
    //qDebug()<<"Вызов";

    qDebug()<<twoRect.topLeft().x();
    qDebug()<<twoRect.topRight().x();

    qDebug()<<twoRect.bottomLeft().y();
    qDebug()<<twoRect.bottomLeft().y();

    qDebug()<<twoRect.left();

   QImage tmp = this->pixmap().toImage();

    for(int x = twoRect.left(); x <twoRect.width();++x)
        for(int y = twoRect.left(); y < twoRect.height();++y)
        {
            qDebug()<<"Вызов";
             tmp.setPixel(x,y,qRgb(0,0,0));
        }
   // this->setPixmap(QPixmap::fromImage(tmp));

    tmp.save("tmp.bmp","BMP");
}
/////



void MyGraphicsItem::setWidthRect(int w)//для высоты
{
    this->w = w;
}

void MyGraphicsItem::setHeightRect(int h)//для ширины
{
    this->h = h;
}


//MyGraphicsItem::MyGraphicsItem(const QPixmap &pm):QObject(), QGraphicsPixmapItem(pm),w(0),h(0)
//{


//}

QPoint MyGraphicsItem::getPoint(){
    return point;
}

MyGraphicsItem::~MyGraphicsItem()
{

}

///для области///

//void MyLabel::scanir()
//{
//    int counter=0;
//    double value;

//    for(int y=0; y<pixmap()->height();y++)
//        for(int x=0; x<pixmap()->width();x++)
//        {
//            twoRect.setCoords(x,y,(x+h),(y+w));
//            if ( pixmap()->copy(twoRect).height() == (w+1) && pixmap()->copy(twoRect).width() == (h+1))
//            {

//                pixmap()->copy(twoRect).toImage().save(QString("C:/Cells/"+ QString::number(counter) +".bmp"),"BMP");
//                //qDebug()<<counter++;
//                //
//                value = std::fabs(Correl((pixmap()->copy(oneRect).toImage()),(pixmap()->copy(twoRect).toImage())));
//                if(value > porog && value < 1.0)
//                {
//                    //qDebug()<< value;
//                    myRect.append(MyRect(twoRect,value));
//                }
//            }

//        }
//    qDebug()<<myRect.count();
//    for(int x = 0;x<myRect.count();++x)
//    {
//        qDebug()<<myRect[x].corr;
//    }
//    //qDebug()<<pixmap()->copy(oneRect).toImage().save("C:/Cells/1.bmp","BMP");
//}
