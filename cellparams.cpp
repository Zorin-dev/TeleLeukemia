
#include <QDebug>

#include "mygraphicsobject.h"



#include <QImage>


#include "cellparams.h"

#include "QtCore/qmath.h"
#include <cmath>

CellParams::CellParams(QImage *image) //img 58 глючит не находит внутреннюю область
{
    S=0;
    img=image;
    imageSize.X=image->width();
    imageSize.Y=image->height();
    CNT=(2*imageSize.Y)*(imageSize.X);
    props= new QVector<CellProps>();
    Coormas = new int[CNT];
    FlPixels = new Coords[imageSize.X*imageSize.Y];
    CNT=0;
}

CellParams::~CellParams()
{
    props->clear();
    delete FlPixels;
    //delete img;
    delete Coormas;
}


void CellParams::ObjSearchWouR()
{
    for(int i = 0;i < imageSize.X; i++) //imageSize.X-1
    {
        for(int j = 1; j < imageSize.Y; j++)
            img->setPixel(i,j,qRgb(0,0,0));
        if(i > 5)
        i+=imageSize.X - 10 ;
    }

    for(int j = 0; j < imageSize.Y; j++) //imageSize.X-1
    {
        for(int i = 1; i < imageSize.X; i++)
            img->setPixel(i,j,qRgb(0,0,0));
        if(j > 5)
        j+=imageSize.Y-10;
    }

    int fillColor=253;
    CNT=0;
    S=0;
    CellProps prop;
    YP=YC=0;
    XP=XC=0;
    PixCnt=0;
    QVector<Coords>* contour;
    contour= new QVector<Coords>();
    QVector<Coords>* body;
    body= new QVector<Coords>();
    for(int i = 1; i < imageSize.X-2; i++) //imageSize.X-1
    {   for(int j = 1; j < imageSize.Y-2; j++)
          {
            int a=(QColor(img->pixel(i,j)).green());
            if ((a==255))
                {
                CNT++;
                prop.XP=i;
                prop.YP=j;
                PixCnt=0;
                int l=0;
                int m=0;
                body->append(Coords(i,j));
                fillPixel(i,j,fillColor);

                     while(PixCnt!=0)
                     {
                      if(PixCnt>0)
                      {
                        m=Coormas[--PixCnt]; l=Coormas[--PixCnt]; //
                                //if(contour->first()==Coords(l+1,m)||contour->first()==Coords(l,m+1)||contour->first()==Coords(l-1,m)||contour->first()==Coords(l,m-1))
                                   // prop.contour=new QVector<Coords>(*contour);
                            if(l+2 < imageSize.X - 1)
                                if ((QColor(img->pixel(l+1,m)).red()==255))
                                {
                                    body->append(Coords(l+1,m));
                                    fillPixel(l+1,m,fillColor);

                                }
                            if(m+2 < imageSize.Y - 1)
                                if ((QColor(img->pixel(l,m+1)).red()==255))
                                {
                                    body->append(Coords(l,m+1));
                                    fillPixel(l,1+m,fillColor);
                                   // FlPixels[S].X=l;
                                    //FlPixels[S].Y=m+1;
                                }

                                   if(l - 2 > 0)
                                        if ((QColor(img->pixel(l-1,m)).red()==255))
                                        {
                                            body->append(Coords(l-1,m));
                                            fillPixel(l-1,m,fillColor);
                                           // FlPixels[S].X=l-1;
                                           // FlPixels[S].Y=m;
                                        }
                                   if(m - 2 > 0)
                                       // else
                                        if ((QColor(img->pixel(l,m-1)).red()==255))
                                        {
                                            body->append(Coords(l,m-1));
                                            fillPixel(l,m-1,fillColor);
                                           // FlPixels[S].X=l;
                                            //FlPixels[S].Y=m-1;
                                        }


                         }
                     }
                     XC=XC/S;
                     YC=YC/S;
                     prop.XC=XC;
                     prop.YC=YC;
                     cnt.X=XC;
                     cnt.Y=YC;
                   //  prop.cnt.X=cnt.X;
                   //  prop.cnt.Y=cnt.Y;
                     prop.S=S;
                     if(S<criteria)
                     {
                         /*while(S>0)
                                {
                                    img->setPixel((FlPixels[S].X),(FlPixels[S].Y),qRgb(1,1,200));
                                    --S;
                                }
                         --CNT;*/
                         QVector<Coords>::const_iterator it;
                             for (it = body->constBegin(); it != body->constEnd(); it++)
                            img->setPixel((it->X),(it->Y),qRgb(1,1,0));
                          body->clear();
                          // //body = new QVector<Coords>();
                      }
                      else
                     {
                      contour = bugContour(prop.XP,prop.YP, fillColor);
                      prop.contour= contour;
                      prop.color=fillColor;
                      //находим крайние значения

                      int right,left,up,bottom,x,y,xprev,yprev;
                      xprev=contour->at(0).X;
                      yprev=contour->at(0).Y;
                      right=0;
                      left=1000000;
                      up=0;
                      bottom=1000000;
                      double shape=0;
                      for(int i=0;i<contour->size();i++)
                      {
                            x=contour->at(i).X;
                            y=contour->at(i).Y;
                              if(x>right)
                                 right=x;
                              if(x<left)
                                  left=x;
                              if(y>up)
                                  up=y;
                              if(y<bottom)
                                  bottom=y;
                              shape+=sqrt((x-xprev)*(x-xprev)+(y-yprev)*(y-yprev))/(sqrt((x-prop.XC)*(x-prop.XC)+(y-prop.YC)*(y-prop.YC)));
                              xprev=x;
                              yprev=y;
                      }
                    prop.P = contour->size();
                    prop.Shape=shape;
                    //prop.color=fill_color;
                    prop.dl.X=left;
                    prop.dl.Y=bottom;
                    prop.ur.X=right;
                    prop.ur.Y=up;


                      if(S>criteria1)
                      {
                          QVector<CellProps>* holes = zaliv(prop.dl, prop.ur, -fillColor );
                          if(holes->size() > 0)
                          {
                              int size;
                              for(int i = 0; i < holes->size(); i++)
                              {
                                  Coords tmp;
                                  size = holes->at(i).contour->size();
                                  if( !(holes->value(i).contour->contains(Coords(prop.dl.X-1,prop.dl.Y-1)) || holes->value(i).contour->contains(Coords(prop.dl.X-1,prop.ur.Y+1)) || holes->value(i).contour->contains(Coords(prop.ur.X+1,prop.ur.Y+1)) || holes->value(i).contour->contains(Coords(prop.ur.X+1,prop.dl.Y-1))))
                                  for(int j = 0; j < size; j++)
                                  {
                                      tmp = holes->value(i).contour->value(j);
                                      prop.contour->append(tmp);
                                  }
                              }
                          }
                        //трансформируем
                          DistanceTransform(contour,body);
                          img->save("dtr" + QString::number(CNT) + ".bmp","BMP");
                          QVector<CellProps>* newProps=watershed(body,fillColor);
                          QMutableVectorIterator<CellProps> it(*newProps);
                          CellProps tmp;
                          while (it.hasNext())
                          {
                              tmp =it.next();
                              QVector<Coords>* contour=bugContour_color(prop.dl,prop.ur, tmp.color);
                              tmp.contour=contour;
                              xprev=contour->at(0).X;
                              yprev=contour->at(0).Y;
                              right=0;
                              left=1000000;
                              up=0;
                              bottom=1000000;
                              shape=0;
                              for(int i=0;i<contour->size();i++)
                              {
                                    x=contour->at(i).X;
                                    y=contour->at(i).Y;
                                      if(x>right)
                                         right=x;
                                      if(x<left)
                                          left=x;
                                      if(y>up)
                                          up=y;
                                      if(y<bottom)
                                          bottom=y;
                                      shape+=sqrt((x-xprev)*(x-xprev)+(y-yprev)*(y-yprev))/(sqrt((x-prop.XC)*(x-prop.XC)+(y-prop.YC)*(y-prop.YC)));
                                      xprev=x;
                                      yprev=y;
                              }
                            //prop.color=fill_color;
                            tmp.dl.X = left;
                            tmp.dl.Y = bottom;
                            tmp.ur.X = right;
                            tmp.ur.Y = up;
                            tmp.P = contour->size();
                            tmp.Shape = shape;

                              props->append(tmp);
                          }
                          //fillColor=fillColor-2;
                          contour->clear();
                          // //contour = new QVector<Coords>();
                          /*for(int i=0; i<newProps->size(); i++)
                          {
                           delete newProps->;
                           delete newProps->value(i).contour;
                           newProps->value(i).contour=NULL;
                           newProps->value(i).body=NULL;
                          }*/
                          //delete newProps;
                      }
                      else
                      {
                         props->append(prop);
                         fillColor=fillColor-2;
                      }
                     }
                     //delete contour;
                     //delete body;

                     //delete newProps;
                      contour= new QVector<Coords>();
                      body= new QVector<Coords>();
                      S=0;
                      cnt.X=cnt.Y=0;

                     //for(int i=0;i<imageSize.X*imageSize.Y;i++)
                     //Coormas[i]=0;
                }
            //else break;
                }
        }
    //int qwe=0;
}

QVector<CellProps>* CellParams::watershed(QVector<Coords> * body, int &initColor)
{
    //int initColor=; //цвет, который был
    QVector<Flood> floods;
    QVector<Coords>* watershed;
    QList<Coords> pixels;
    watershed = new QVector<Coords>();
    QHash<int,Coords> b;
    int x,y,color=0;
    QVector<Coords>::const_iterator it1;
    QList<Coords>::const_iterator it;
    for(it1=body->constBegin();it1!=body->constEnd();it1++)
    {
        //x=body->at(i).X;
        //y=body->at(i).Y;
        b.insertMulti(QColor(img->pixel(it1->X,it1->Y)).red(), Coords(it1->X,it1->Y));
    }
    int cnt;
    int elem=0;

    for (int col=0; col<255;col++)
    {
        pixels=b.values(col);
        //while(pixels.size()>0)
        for(it=pixels.constBegin();it!=pixels.constEnd();it++)
        {
            x=it->X;
            y=it->Y;
            //color=QColor(img->pixel(x,y)).red();
            //if (color==col)
                /*if(floods.size()==0)
                {
                    QHash<int,int> hs;
                    hs.insert(x*10000+(y),color);
                    floods.append(hs);
                */
                cnt=0;
                int cntOne=0;
                int thresh=0;
                int same=0;
                color=qRed(img->pixel(x,y));

                //#########проверим, если пиксель окружен дубликатами#############
                if ((QColor(img->pixel(x+1,y)).red()==color))
                    {
                        same++;
                    }
                if ((QColor(img->pixel(x,y+1)).red()==color))
                    {
                        same++;
                    }
                if ((QColor(img->pixel(x-1,y)).red()==color))
                    {
                        same++;
                    }
                if ((QColor(img->pixel(x,y-1)).red()==color))
                    {
                        same++;
                    }
                if ((QColor(img->pixel(x+1,y+1)).red()==color))
                    {
                        same++;
                    }
                if ((QColor(img->pixel(x-1,y+1)).red()==color))
                    {
                        same++;
                    }
                if ((QColor(img->pixel(x-1,y-1)).red()==color))
                    {
                        same++;
                    }
                if ((QColor(img->pixel(x+1,y-1)).red()==color))
                    {
                        same++;
                    }
                int kk=floods.size();
                for (int k=0;k<kk;k++)
                {
                    cntOne=0;
                    //#########смоторим, куда скатывается############# //перепилить через итератор обращение к k-му бассейну.
                if(x + 1 < img->size().width())
                    if ((QColor(img->pixel(x+1,y)).red()<=color+thresh))
                        if(floods[k].body.contains((x+1)*10000+(y)))
                        {
                            cntOne++;
                            elem=k;
                        }
                if(y + 1 < img->size().height())
                    if ((QColor(img->pixel(x,y+1)).red()<=color+thresh))
                        if(floods[k].body.contains((x)*10000+(y+1)))
                        {
                            cntOne++;
                            elem=k;
                        }
                if(x - 1 > 0)
                    if ((QColor(img->pixel(x-1,y)).red()<=color+thresh))
                        if(floods[k].body.contains((x-1)*10000+(y)))
                        {
                            cntOne++;
                            elem=k;
                        }
                if(y - 1 > 0)
                    if ((QColor(img->pixel(x,y-1)).red()<=color+thresh))
                        if(floods[k].body.contains((x)*10000+(y-1)))
                        {
                            cntOne++;
                            elem=k;
                        }
                if(y + 1 < img->size().height() && x + 1 < img->size().width())
                    if ((QColor(img->pixel(x+1,y+1)).red()<=color+thresh))
                        if(floods[k].body.contains((x+1)*10000+(y+1)))
                        {
                            cntOne++;
                            elem=k;
                        }
                if(x - 1 > 0 && y + 1 < img->size().height())
                    if ((QColor(img->pixel(x-1,y+1)).red()<=color+thresh))
                        if(floods[k].body.contains((x-1)*10000+(y+1)))
                        {
                            cntOne++;
                            elem=k;
                        }
                if(x - 1 > 0 && y - 1 > 0)
                    if ((QColor(img->pixel(x-1,y-1)).red()<=color+thresh))
                        if(floods[k].body.contains((x-1)*10000+(y-1)))
                        {
                            cntOne++;
                            elem=k;
                        }
                if(y - 1 > 0 && x + 1 < img->size().width())
                    if ((QColor(img->pixel(x+1,y-1)).red()<=color+thresh))
                        if(floods[k].body.contains((x+1)*10000+(y-1)))
                        {
                            cntOne++;
                            elem=k;
                        }
                    if(cntOne>0)
                        cnt++;

                }
                if(cnt==1)
                {
                    int color=QColor(img->pixel(x,y)).red();
                    floods[elem].body.insert(((x)*10000+(y)), color);
                    img->setPixel(x,y,qRgb(0, floods[elem].color, 0)); //сделать так, чтобы цвета продолжались от тех, что при заливке (сделать заливку разными цветами)

                }
                if(cnt>1) //&&floods[n_biggest].size()>500
                {
                    watershed->append(Coords((x),(y)));
                }
                if(cnt==0)
                {
                    if (same>2 )
                    {
                        b.insertMulti(col+1,Coords(x,y));
                        img->setPixel(x,y,qRgb(col+1, 150, 25));
                        //pixels.swap(i,pixels.size()-1);
                        //pixels.append(Coords(x,y));
                    }
                    else
                    {
                        //pixels.removeAt(i);
                        //i--;
                    Flood h;
                    h.body.insert((x)*10000+(y),QColor(img->pixel(x,y)).red());
                    h.fPoint=Coords(x,y);
                    h.color=initColor;

                    double dst=100000.0;
                    double Ndst=0.0;
                    int i=0;
                    QVector<Flood>::const_iterator Fit;
                    for(Fit=floods.constBegin(); Fit!=floods.constEnd(); Fit++)
                    {
                        Ndst=qSqrt(qPow((Fit->fPoint.X-x),2.0)+(qPow((Fit->fPoint.Y-y),2.0)));
                        if(Ndst<dst)
                        {
                            elem=i;
                            dst=Ndst;
                        }
                        i++;
                    }

                    if(dst>100)
                        {
                            img->setPixel(x,y,qRgb(QColor(img->pixel(x,y)).red(),255,1));
                            floods.append(h);
                            initColor=initColor-2;
                        }
                    else
                        {
                            floods[elem].body.insert(((x)*10000+(y)), color);
                            img->setPixel(x,y,qRgb(0, floods[elem].color, 0));// b.insertMulti(col+1,Coords(x,y)); раньше оставляли на потом. Теперь просто добавим к ближайшему водоему
                        }
                    }
                }



        }

    }
    QVector<CellProps>* cp= new QVector<CellProps>();
    QVector<Flood>::const_iterator Fit;
    CellProps prop;
    for(Fit=floods.constBegin(); Fit!=floods.constEnd(); Fit++)
    {
      //for(it=Fit->body.constBegin();it!=Fit->body.constEnd(); it++)
        int s=Fit->body.size();
        if(s>criteria) //критерий с ввода
          {
            prop.color=Fit->color;
            prop.S=s;
            prop.XC=Fit->fPoint.X;
            prop.YC=Fit->fPoint.Y;
            prop.XP=0;
            prop.YP=0;
            cp->append(prop);
          }
    }
    watershed->clear();
    return cp;
}

void CellParams::zalivWour(int x, int y)
{
    Coormas[PixCnt++]=x;
    Coormas[PixCnt++]=y;
     img->setPixel(x,y,qRgb(200,1,1));
     S++;
   XC=XC+x;
   YC=YC+y;

}

void CellParams::fillPixel(int x, int y, int color)
{
    Coormas[PixCnt++]=x;
    Coormas[PixCnt++]=y;
    if(color > 0)
     img->setPixel(x,y,qRgb(0,color,1));
    else
     img->setPixel(x,y,qRgb(1,-color + 1,-color));
     S++;
   XC=XC+x;
   YC=YC+y;

}


void CellParams::DistanceTransform(QVector<Coords>* contour,QVector<Coords>* body)
{
    int h;
    double dst_curr=10000;
    double dst_new(dst_curr);
    double dst_max=0;
    QVector<double> dst;


    QVector<Coords>::const_iterator b_it;
    QVector<Coords>::const_iterator c_it;
        //for (it = body->constBegin(); it != body->constEnd(); b_it++)


   // QVectorIterator<Coords> b_it(body);
    Coords cCoord;
    Coords bCoord;

    int cSize=contour->size();
    int i=0;
    int shag=1;
    int x1=0;
    int y1=0;
    int x2=0;
    int y2=0;
    if(cSize>360)
        shag=cSize/360;
   // QVectorIterator<Coords> c_it(contour);
    for (b_it = body->constBegin(); b_it != body->constEnd(); b_it++) // for(int i=0;i<body->size();i++)
   {    //bCoord=b_it.next();
        while (i < cSize)    //  for(int j=0;j<contour->size();j++)
       {
        x1=contour->at(i).X;
        y1=contour->at(i).Y;
        x2=b_it->X;
        y2=b_it->Y;


        //cCoord=c_it.next();
        dst_new=sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
        if(dst_new<dst_curr)
            dst_curr=dst_new;
        i=i+shag;
        img->setPixel(x1,y1,qRgb(0,0,250)); //вывод шага
       }
       i=0;
       dst.append(dst_curr);
       if(dst_curr>dst_max)
           dst_max=dst_curr;
        dst_curr=1000;

   }

 //  b_it=body->constbegin();
    i=0;
   for (b_it = body->constBegin(); b_it != body->constEnd(); b_it++)//for(int i=0; i<body->size();i++)
   {
      // bCoord=b_it.next();
       h=static_cast<int>((dst[i]/dst_max)*255);

       img->setPixel(b_it->X,b_it->Y,qRgb(255-h,0,0));
       i++;
   }
  // h=static_cast<int>(dst);
   //img->setPixel(i.X,i.Y,qRgb(static_cast<int>(dst),static_cast<int>(dst),static_cast<int>(dst)));

}

//void CellParams::DistanceTransform_color(CellProps prop, int color_thresh)
//{
//    QVector<Coords>* contour= prop.contour;
//    int h;
//    double dst_curr=10000;
//    double dst_new(dst_curr);
//    double dst_max=0;
//    QVector<double> dst;
//    for(int x=0; x<prop.downright.X-prop.upleft.X;x++) //imageSize.X-1
//    {   for(int y=0; y<prop.upleft.Y-prop.downright.Y;y++)
//        {
//            if(img->pixel(x,y)==prop.color)
//            {
//            for(int j=0;j<contour->size();j++)
//                {
//                     dst_new=qSqrt(qPow((contour->at(j).X-x),2.0)+(qPow((contour->at(j).Y-y),2.0)));
//                        if(dst_new<dst_curr)
//                    dst_curr=dst_new;
//                }
//        dst.append(dst_curr);
//        if(dst_curr>dst_max)
//           dst_max=dst_curr;
//        dst_curr=1000;
//            }
//        }
//   }
//    int ind=0;
//    for(int x=0; x<prop.downright.X-prop.upleft.X;x++) //imageSize.X-1
//    {   for(int y=0; y<prop.upleft.Y-prop.downright.Y;y++)
//        {
//            if(img->pixel(x,y)==prop.color)
//            {
//                 h=static_cast<int>((dst[ind]/dst_max)*255);
//                 if(h>color_thresh)
//                 img->setPixel(x,y,qRgb(255-h,qGreen(prop.color),qBlue(prop.color)));
//                 ind++;
//            } //переделать
//         }
//    }
//  // h=static_cast<int>(dst);
//   //img->setPixel(i.X,i.Y,qRgb(static_cast<int>(dst),static_cast<int>(dst),static_cast<int>(dst)));

//}


QVector<Coords>* CellParams::bugContour(int x, int y, int color)
{


    char direction='l';
    QVector<Coords>* contour = new QVector<Coords>();

    Coords first(x,y);
    Coords curr(x,y);

    if((QColor(img->pixel(x,y+1)).green()!=color))
        {
            //curr.Y++;
            curr.X++;
            direction ='r';
        }
    else
        {
            curr.Y++;
            direction ='u';

        }



    while(!(curr==first))
    {
         switch (direction)
         {
         case 'u':
         {
            if((QColor(img->pixel(curr.X,curr.Y)).green()==color))
            {
                if (QColor(img->pixel(curr.X,curr.Y-1)).green()!=color)
                    contour->append(Coords(curr.X,curr.Y-1));
                if(curr.X > 0)
                    curr.X--;
                    direction = 'l';
            //    img->setPixel(curr.X,curr.Y,qRgb(0,255,255));
            }
            else
            {
                if (QColor(img->pixel(curr.X,curr.Y-1)).green()==color)
                    contour->append(Coords(curr.X,curr.Y));
                if (curr.X < imageSize.X - 1)
                curr.X++;
                direction ='r';

            }
            break;
         }
         case 'l':
         {
             if((QColor(img->pixel(curr.X,curr.Y)).green()==color))
             {
                 if (QColor(img->pixel(curr.X+1,curr.Y)).green()!=color)
                     contour->append(Coords(curr.X+1,curr.Y));
                 if(curr.Y > 0)
                 curr.Y--;
                 direction = 'd';
            //   img->setPixel(curr.X,curr.Y,qRgb(0,255,255));
             }
             else
             {
                 if (QColor(img->pixel(curr.X+1,curr.Y)).green()==color)
                    contour->append(Coords(curr.X,curr.Y));
                 if(curr.Y < imageSize.Y - 1 )
                 curr.Y++;
                 direction ='u';

             }
             break;
         }
         case 'd':
         {
             if((QColor(img->pixel(curr.X,curr.Y)).green()==color))
             {
                 if (QColor(img->pixel(curr.X,curr.Y+1)).green()!=color)
                     contour->append(Coords(curr.X,curr.Y+1));
                 if (curr.X < imageSize.X - 1)
                 curr.X++;
                 direction = 'r';
              // img->setPixel(curr.X,curr.Y,qRgb(0,255,255));
             }
             else
             {
                 if (QColor(img->pixel(curr.X,curr.Y+1)).green()==color)
                     contour->append(Coords(curr.X,curr.Y));
                 if (curr.X > 0)
                 curr.X--;
                 direction ='l';

             }
             break;
         }
         case 'r':
         {
             if((QColor(img->pixel(curr.X,curr.Y)).green()==color))
             {
                 if (QColor(img->pixel(curr.X-1,curr.Y)).green()!=color)
                     contour->append(Coords(curr.X-1,curr.Y));
                 if (curr.Y < imageSize.Y - 1)
                 curr.Y++;
                 direction = 'u';
             //  img->setPixel(curr.X,curr.Y,qRgb(0,255,255));
             }
             else
             {
                 if (QColor(img->pixel(curr.X-1,curr.Y)).green()==color)
                     contour->append(Coords(curr.X,curr.Y));
                 if (curr.Y > 0)
                 curr.Y--;
                 direction ='d';

             }
             break;
         }

         }
    }
    return contour;


}

QVector<Coords>* CellParams::bugContour_color(Coords dl, Coords ur, int color)
{


    char direction='l';
    QVector<Coords>* contour = new QVector<Coords>();
    int x=0,y=0;
    int i=dl.X-1;
    while(i<ur.X)//for(int i=dl.X; i<ur.X ;i++) //imageSize.X-1
    {   for(int j=dl.Y-1; j<ur.Y;j++)
          {
            int a=(QColor(img->pixel(i,j)).green());
            if ((a==color))
            {
                x=i;
                y=j;
                break;
            }
          }
        i++;
        if(x!=0)
            break;
    }
    //return bugContour(x,y,color);

    Coords first(x,y);
    Coords curr(x,y);

    if((QColor(img->pixel(x,y+1)).green()!=color))
        {
            //curr.Y++;
            curr.X++;
            direction ='r';
        }
    else
        {
            curr.Y++;
            direction ='u';

        }


    while(!(curr==first))
    {
         switch (direction)
         {
         case 'u':
         {

            if((QColor(img->pixel(curr.X,curr.Y)).green()==color))
            {
                if (QColor(img->pixel(curr.X,curr.Y-1)).green()!=color)
                    contour->append(Coords(curr.X,curr.Y));
                if (curr.X > 0)
                curr.X--;
                direction = 'l';
            //    img->setPixel(curr.X,curr.Y,qRgb(0,255,255));
            }
            else
            {
                if (QColor(img->pixel(curr.X,curr.Y-1)).green()==color)
                    contour->append(Coords(curr.X,curr.Y-1));
                if (curr.X < imageSize.X - 1)
                curr.X++;
                direction ='r';

            }
            break;
         }
         case 'l':
         {
             if((QColor(img->pixel(curr.X,curr.Y)).green()==color))
             {
                 if (QColor(img->pixel(curr.X+1,curr.Y)).green()!=color)
                     contour->append(Coords(curr.X,curr.Y));
                 if (curr.Y > 0)
                 curr.Y--;
                 direction = 'd';
            //   img->setPixel(curr.X,curr.Y,qRgb(0,255,255));
             }
             else
             {
                 if (QColor(img->pixel(curr.X+1,curr.Y)).green()==color)
                     contour->append(Coords(curr.X+1,curr.Y));
                 if (curr.Y < imageSize.Y - 1)
                 curr.Y++;
                 direction ='u';

             }
             break;
         }
         case 'd':
         {
             if((QColor(img->pixel(curr.X,curr.Y)).green()==color))
             {
                 if (QColor(img->pixel(curr.X,curr.Y+1)).green()!=color)
                     contour->append(Coords(curr.X,curr.Y));
                 if (curr.X < imageSize.X - 1)
                 curr.X++;
                 direction = 'r';
              // img->setPixel(curr.X,curr.Y,qRgb(0,255,255));
             }
             else
             {
                 if (QColor(img->pixel(curr.X,curr.Y+1)).green()==color)
                     contour->append(Coords(curr.X,curr.Y+1));
                 if (curr.X > 0)
                 curr.X--;
                 direction ='l';

             }
             break;
         }
         case 'r':
         {
             if((QColor(img->pixel(curr.X,curr.Y)).green()==color))
             {
                 if (QColor(img->pixel(curr.X-1,curr.Y)).green()!=color)
                     contour->append(Coords(curr.X,curr.Y));
                 if (curr.Y < imageSize.Y - 1)
                 curr.Y++;
                 direction = 'u';
             //  img->setPixel(curr.X,curr.Y,qRgb(0,255,255));
             }
             else
             {
                 if (QColor(img->pixel(curr.X-1,curr.Y)).green()==color)
                     contour->append(Coords(curr.X-1,curr.Y));
                 if (curr.Y > 0)
                 curr.Y--;
                 direction ='d';

             }
             break;
         }

         }
    }
    return contour;


}


int CellParams::getCNT()
{
    return CNT;
}

void CellParams::setCriteria(int crt)
{
    criteria=crt;
}
int CellParams::getCriteria()
{
    return criteria;
}

void CellParams::setCriteria1(int crt)
{
    criteria1=crt;
}
int CellParams::getCriteria1()
{
    return criteria1;
}

QVector<CellProps>* CellParams::getCellProps()
{
    return props;
}



QVector<CellProps>* CellParams::zaliv(Coords dl, Coords ur, int color)
{
    //CNT=(2*ur.Y-dl.Y)*(ur.X-dl.X);
    //Coormas = new int[CNT];
    int fillColor = color;
    CNT = 0;
    S  = 0;
    QVector<CellProps>* props = new QVector<CellProps>();
    CellProps prop;
    prop.XC=prop.XP=prop.S=XP=XC=0;
    prop.YC=prop.YP=YP=YC=0;
    prop.contour= new QVector<Coords>();
    prop.body= new QVector<Coords>();
    PixCnt = 0;
    QVector<Coords>* contour;
    contour= new QVector<Coords>();
    QVector<Coords>* body;
    body= new QVector<Coords>();

    for(int i=dl.X; i<ur.X;i++) //imageSize.X-1
    {   for(int j=dl.Y; j<ur.Y;j++)
          {
            int a=(QColor(img->pixel(i,j)).green());
            if ((a==0))
                {
                CNT++;
                prop.XP=i;
                prop.YP=j;
                PixCnt=0;
                int l=0;
                int m=0;
                body->append(Coords(i,j));
                fillPixel(i,j,fillColor);

                     while(PixCnt!=0)
                     {
                      if(PixCnt>0)
                      {
                        m=Coormas[--PixCnt]; l=Coormas[--PixCnt]; //
                                //if(contour->first()==Coords(l+1,m)||contour->first()==Coords(l,m+1)||contour->first()==Coords(l-1,m)||contour->first()==Coords(l,m-1))
                                   // prop.contour=new QVector<Coords>(*contour);
                            if(l + 1 < ur.X)
                                if ((QColor(img->pixel(l+1,m)).green()==0))
                                {
                                    body->append(Coords(l+1,m));
                                    fillPixel(l+1,m,fillColor);

                                }
                            if(m + 1 < ur.Y)
                                if ((QColor(img->pixel(l,m+1)).green()==0))
                                {
                                    body->append(Coords(l,m+1));
                                    fillPixel(l,1+m,fillColor);
                                   // FlPixels[S].X=l;
                                    //FlPixels[S].Y=m+1;
                                }

                                   if(l - 1 > dl.X)
                                        if ((QColor(img->pixel(l-1,m)).green()==0))
                                        {
                                            body->append(Coords(l-1,m));
                                            fillPixel(l-1,m,fillColor);
                                           // FlPixels[S].X=l-1;
                                           // FlPixels[S].Y=m;
                                        }
                                   if(m - 1 > dl.Y)
                                       // else
                                        if ((QColor(img->pixel(l,m-1)).green()==0))
                                        {
                                            body->append(Coords(l,m-1));
                                            fillPixel(l,m-1,fillColor);
                                           // FlPixels[S].X=l;
                                            //FlPixels[S].Y=m-1;
                                        }


                         }
                     }
                     if(S != 0)
                     {
                         XC=XC/S;
                         YC=YC/S;
                     }
                     prop.XC=XC;
                     prop.YC=YC;
                     cnt.X=XC;
                     cnt.Y=YC;
                   //  prop.cnt.X=cnt.X;
                   //  prop.cnt.Y=cnt.Y;
                     prop.S=S;
                     if(S < 200 || S > 8000)
                     {
                         /*while(S>0)
                                {
                                    img->setPixel((FlPixels[S].X),(FlPixels[S].Y),qRgb(1,1,200));
                                    --S;
                                }
                         --CNT;*/
                         QVector<Coords>::const_iterator it;
                             for (it = body->constBegin(); it != body->constEnd(); it++)
                             {
                                if(S > 8000)
                                    img->setPixel((it->X),(it->Y),qRgb(1,1,1));
                                if(S < 50)
                                    img->setPixel((it->X),(it->Y),qRgb(1,-color,1));
                             }

                             contour->clear();
                             body->clear();
                      }
                      else
                     {
                      contour = bugContour(prop.XP,prop.YP, -fillColor + 1);
                      prop.contour = contour;
                      prop.color = fillColor;
                      //находим крайние значения

                      if (contour->size() != 0)
                      {
                        int right,left,up,bottom,x,y,xprev,yprev;
                        xprev=contour->at(0).X;
                        yprev=contour->at(0).Y;
                        right=0;
                        left=1000000;
                        up=0;
                        bottom=1000000;
                        double shape=0;
                      for(int i=0;i<contour->size();i++)
                      {
                            x=contour->at(i).X;
                            y=contour->at(i).Y;
                            left=x;
                        if(y>up)
                            up=y;
                        if(y<bottom)
                            bottom=y;
                        shape+=sqrt((x-xprev)*(x-xprev)+(y-yprev)*(y-yprev))/(sqrt((x-prop.XC)*(x-prop.XC)+(y-prop.YC)*(y-prop.YC)));
                        xprev=x;
                        yprev=y;
                }
              prop.P = contour->size();
              prop.Shape=shape;
              //prop.color=fill_color;
              prop.dl.X=left;
              prop.dl.Y=bottom;
              prop.ur.X=right;
              prop.ur.Y=up;
              props->append(prop);
              }
              fillColor = fillColor + 2;

               }
               //contour->clear();
               //body->clear();
                     /*for(int i=0; i<newProps->size(); i++)
                     {
                         newProps->
                     }*/
                      contour = new QVector<Coords>();
                      body = new QVector<Coords>();
                      S=0;
                      cnt.X=cnt.Y=0;

                     //for(int i=0;i<imageSize.X*imageSize.Y;i++)
                     //Coormas[i]=0;
                }
        }
    }
    return props;
}
QVector<CellProps>*  CellParams::calculate()
{
   ObjSearchWouR();
}

