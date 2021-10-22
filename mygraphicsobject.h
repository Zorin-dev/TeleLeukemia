#ifndef MYGRAPHICSOBJECT_H
#define MYGRAPHICSOBJECT_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

/////
#include <QPainter>
#include <QMouseEvent>

struct MyRect//класс для квадратиков
{
    QRect myrect;
    double corr;
    MyRect():corr(0.0){}
    MyRect(QRect nmyrect,double ncorr):myrect(nmyrect),corr(ncorr){}
};
/////

class MyGraphicsItem : public QObject, public QGraphicsPixmapItem
{
Q_OBJECT

public:

MyGraphicsItem(QGraphicsItem *parent = 0): QObject(), QGraphicsPixmapItem(parent)
        {

        }

MyGraphicsItem(const QPixmap & pixmap, QGraphicsItem * parent = 0 ): QObject(),
                                                                     QGraphicsPixmapItem(pixmap, parent)
        {

        }

 //   MyGraphicsItem(const QPixmap& pm);
    ~MyGraphicsItem();

    void paint(QPainter *p, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    //signals:

    QImage getImage();//Рефактроринг - копирование области для сохранения

    /////
    //  void paintEvent(QPaintEvent *e);
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

    void calc();


    void setOneImage(const QImage & src);
    void setTwoImage(const QImage & src);
    QPoint getPoint();

    bool selectionStarted;

    QRect oneRect;
    QRect twoRect;
    QRect selectionRect;

    QVector<MyRect> myRect;



    void setWidthRect(int w);
    void setHeightRect(int h);

    int w;
    int h;
    QPoint point;

signals:
    void MouseClicked();
    /////






};

#endif // MYGRAPHICSOBJECT_H
