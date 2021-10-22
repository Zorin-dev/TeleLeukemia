#include "propdialog.h"
#include "ui_propdialog.h"
#include <QDir>

const QString PropDialog::PERIMETER = "Perimeter";
const QString PropDialog::SQUARE = "S";
const QString PropDialog::SHAPE = "Shape";
const QString PropDialog::CITOPLASM_RATIO = "CitoplasmRatio";
const QString PropDialog::ROUNDNESS = "Roundness";
const QString PropDialog::RECTANGLE_FILL = "RectangleFill";
const QString PropDialog::CITOPLASM_HUE = "CitoplasnHue";
const QString PropDialog::NUCLEAR_BRIGHTNESS = "NuclaerBrightness";
const QString PropDialog::CONTOUR_MOMENT = "ContourMoment";
const QString PropDialog::X_COORD_OF_CENTER = "XC";
const QString PropDialog::y_COORD_OF_CENTER = "YC";
const QString PropDialog::IMAGE_NAME = "ImgName";
const QString PropDialog::SUB_IMAGE_NUMBER = "SubImgNumber";
const QString PropDialog::CELL_CLASS = "CellClass";

PropDialog::PropDialog(QWidget *parent, QImage* img, QImage * dst) :
    QDialog(parent),my(0),
    ui(new Ui::PropDialog)
{
    ui->setupUi(this);
 //   int i=0;
    this->img=img;
    this->dst=dst;
    ui->graphicsView->setScene(&sc);
    for(int i = 0 ;i < 100; i++)
    ui->listWidget->addItem(QString::number(i));
    my = new MyGraphicsItem(QPixmap());
    sc.addItem(my);
    props = new QVector<CellProps>();

    mini = NULL;

    strList << PERIMETER << SQUARE << SHAPE << CITOPLASM_RATIO
            << ROUNDNESS << RECTANGLE_FILL << CITOPLASM_HUE << NUCLEAR_BRIGHTNESS
            << CONTOUR_MOMENT << X_COORD_OF_CENTER << y_COORD_OF_CENTER << IMAGE_NAME
            << SUB_IMAGE_NUMBER << CELL_CLASS ;
    strData.addRow(strList);
    strList.clear();
    fileName = QString("");
    cellsClass = 0;
}

PropDialog::~PropDialog()
{
    delete ui;
}

void PropDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{
    if(props->size()!= 0)
    {
    ui->radioButton->setChecked(true);
    if (mini != NULL)
        delete mini;

    int index = ui->listWidget->row(item);
    if (index > 0)
    {
        if(index < props->size() - 1)
        {
        ui->lineEdit->setText(QString::number(props->at(index).XC));
        ui->lineEdit_2->setText(QString::number(props->at(index).YC));
        ui->lineEdit_5->setText(QString::number(props->at(index).S));
        //ui->lineEdit_6->setText(QString::number(props->at(index).color));
        ui->lineEdit_3->setText(QString::number(props->at(index).Shape));
        index=ui->listWidget->currentIndex().row();
        int color = props->at(index).color;
        int h = props->at(index).ur.Y - props->at(index).dl.Y;
        int w = props->at(index).ur.X - props->at(index).dl.X;
        QImage * mini = new QImage(w, h, img->format() );
        int x=0,y=0;
        int x1=props->at(index).ur.X;
        int y1=props->at(index).ur.Y;
        for(int i=props->at(index).dl.X; i<x1 ;i++) //imageSize.X-1
        {   for(int j=props->at(index).dl.Y; j<y1;j++)
              {
                int a=(QColor(dst->pixel(i,j)).green());
                if ((a==color))
                {
                  mini->setPixel(x,y,img->pixel(i,j));
                }
                else
                    mini->setPixel(x,y,qRgb(0,0,0));
                y++;
              }
            y=0;
            x++;
        }
        // my = new MyGraphicsItem(QPixmap::fromImage(*mini));
        //my = new MyGraphicsItem(QPixmap::fromImage(*mini));
        if(mini)
        my->setPixmap(QPixmap::fromImage(*mini));
    //my->setPixmap(QPixmap::fromImage(*mini));
   //sc.addItem(my);
   //delete mini;
  //  delete my;
        }
      }
    }
}

void PropDialog::setProps(QVector<CellProps> * pr)
{
    props=pr;
    ui->listWidget->clear();
    for(int i = 0; i < props->size(); i++)
    {
        ui->listWidget->addItem(QString::number(i));
    }
//    for(int i=1;i<props->size();i++)
//        ui->listWidget->model()->setData(QModelIndex();QString::number(i+1)) item(i)->setText(QString::number(i+1));
}

void PropDialog::setImage(QImage &src)
{
    img=new QImage(src);
}

void PropDialog::setDst(QImage &dst)
{
    this->dst=new QImage(dst);
}

void PropDialog::clear()
{
//ui->listWidget->clear();
    //if(img)
        //delete img,dst;
    //this->props->clear();

//      int n = ui->listWidget->count() - 1;
//      for(int j = ui->listWidget->count() - 1; j>=0; j--) {
//        //QListWidgetItem *it = ui->listWidget->takeItem(1);
//        ui->listWidget->item(j)->setText("-");
        //ui->listWidget->model()->removeRow(1, QModelIndex());
        //delete it;
//      }

      //ui->listWidget->clear();
//      ui->listWidget = new QWidget();
}

QPushButton* PropDialog::getButton()
{
    return ui->pushButton;
}

QImage* PropDialog::getImage()
{
    return img;
}


QImage* PropDialog::getDst()
{
    return dst;
}



void PropDialog::on_pushButton_clicked()
{
    int index = 0;
    index=ui->listWidget->currentIndex().row();
   QVector<Coords>::iterator i = props->at(index).contour->begin();
    while (i!=props->at(index).contour->end())
    {
        img->setPixel(i->X,i->Y,qRgb(0,255,0));
        i++;
    }
   PressSgn();
}


void PropDialog::on_pushButton_2_clicked()
{

       // strList << "121" << "32" << "45";
       // strData << strList << "this is not the last row";
       // strData.insertRow(1, strList);

        // write to file


    for(int index = 0; index<props->size(); index++)
    {
        if((*props)[index].P < 100) props->remove(index);
        else
        {
        int color = props->at(index).color;
        int h = props->at(index).ur.Y - props->at(index).dl.Y;
        int w = props->at(index).ur.X - props->at(index).dl.X;
        QImage *cellNuclei = new QImage(w, h, img->format() );
        QImage *cellMask = new QImage(w, h, img->format() );
        QImage *mini_backg = new QImage(w, h, img->format() );
        QImage *cellCitoplasm = new QImage(w, h, img->format() );
        QImage *cellWithEverything = new QImage(w, h, img->format() );
        int x=0,y=0;
        int x1=props->at(index).ur.X;
        int y1=props->at(index).ur.Y;
        double brightness = 0.0;
        for(int i=props->at(index).dl.X; i<x1 ;i++) //imageSize.X-1
        {   for(int j=props->at(index).dl.Y; j<y1;j++)
              {
                int a=(QColor(dst->pixel(i,j)).green());
                if ((a==color))
                {
                  cellNuclei->setPixel(x,y,img->pixel(i,j));
                  cellWithEverything->setPixel(x,y,img->pixel(i,j));
                  brightness += (0.59*(QColor(img->pixel(i,j)).green() + 0.3*QColor(img->pixel(i,j)).red() + 0.11*QColor(img->pixel(i,j)).blue()));
                }
                else{
                    cellNuclei->setPixel(x,y,qRgb(0,0,0));
                    cellWithEverything->setPixel(x,y,img->pixel(i,j));
                    //mini1->setPixel(x,y,img->pixel(i,j));//
                    mini_backg->setPixel(x,y,img->pixel(i,j));
                }

                cellMask->setPixel(x,y,img->pixel(i,j));
                y++;
              }
            y=0;
            x++;
        }
        brightness /= (*props)[index].S;
        (*props)[index].nuclearBrightness = brightness;

        calculateCellMask(cellMask, cellNuclei);

        int S = 0; //площадь цитоплазмы

        for(int i = 0; i < cellMask->width() ;i++) //imageSize.X-1
        {   for(int j = 0; j < cellMask->height();j++){
                if(QColor(cellMask->pixel(i,j)).green() == 100){
                    cellCitoplasm->setPixel(i,j,QColor(mini_backg->pixel(i,j)).rgb());
                    S++;
                }
                else
                    cellCitoplasm->setPixel(i,j, qRgb(0,0,0));
            }
        }

       (*props)[index].citoplasmRatio = props->value(index).S/S;
       (*props)[index].rectFill = h*w / props->value(index).S;
       (*props)[index].roundCoef = (4*3.1415*props->value(index).S) / ((props->value(index).P)*(props->value(index).P));

        //подсчет оттенка цитоплазмы.
        double citoplasmHue = 0;
        for(int i = 0; i < cellMask->width() ;i++) //imageSize.X-1
        {   for(int j = 0; j < cellMask->height();j++){
                if(QColor(cellCitoplasm->pixel(i,j)).green() > 0) {
                   citoplasmHue += QColor(cellCitoplasm->pixel(i,j)).hsvHue();
                }
            }
        }
        (*props)[index].citoplasmHue = citoplasmHue / S;

        //расчет момента границ ядра
        double Mxx = 0.0;
        double Mxy = 0.0;
        double Myy = 0.0;
        int xi, yi = 0;
        for(int i = 0; i < (*props)[index].contour->length();i++){
            xi = (*props)[index].contour->at(i).X;
            yi = (*props)[index].contour->at(i).Y;
            Mxx += (xi -(*props)[index].XC)*(xi -(*props)[index].XC);
            Myy += (yi -(*props)[index].YC)*(yi -(*props)[index].YC);
            Mxy += (xi -(*props)[index].XC)*(yi -(*props)[index].YC);
        }
        (*props)[index].M = ( 0.5*(Mxx + Myy) - 0.25*qSqrt(0.25*(Mxx-Myy)*(Mxx-Myy) + Mxy*Mxy)) / ( 0.5*(Mxx + Myy) + 0.25*qSqrt(0.25*(Mxx-Myy)*(Mxx-Myy) + Mxy*Mxy));

       MyGraphicsItem* my1 = new MyGraphicsItem(QPixmap::fromImage(*cellNuclei));

       //save all
       my1->setPixmap(QPixmap::fromImage(*cellWithEverything));
     //  QString str("out00" + QString(index) + ".bmp");
       QDir dir(path);
       QString path = "out/" + this->path;
       if(!QFile::exists(path)){
          dir.mkpath(path); //имя класса а не номер
       }
       my1->getImage().save(path + imgName  + "-" + QString::number(index) + ".bmp","BMP");

       //save mask
       my1->setPixmap(QPixmap::fromImage(*cellMask));
       my1->getImage().save(path + imgName  + "-" + QString::number(index) + "(mask).bmp","BMP");

       //save cito
       my1->setPixmap(QPixmap::fromImage(*cellCitoplasm));
       my1->getImage().save(path + imgName  + "-citoplasm" + QString::number(index) + ".bmp","BMP");

       //save nuclei
       my1->setPixmap(QPixmap::fromImage(*cellNuclei));
       my1->getImage().save(path + imgName  + "-" + QString::number(index) + "(nuclei).bmp","BMP");

       delete my1;
       delete cellNuclei;
       delete cellMask;
       cellMask = NULL;
       delete mini_backg;
       delete cellCitoplasm;
       delete cellWithEverything;
      // sc.addItem(my);


       strList << QString::number(props->at(index).P)
               << QString::number(props->at(index).S)
               << QString::number(props->at(index).Shape)
               << QString::number(props->at(index).citoplasmRatio)
               << QString::number(props->at(index).roundCoef)
               << QString::number(props->at(index).rectFill)
               << QString::number(props->at(index).citoplasmHue)
               << QString::number(props->at(index).nuclearBrightness)
               << QString::number(props->at(index).M)
               << QString::number(props->at(index).XC)
               << QString::number(props->at(index).YC)
               << path + imgName
               << QString::number(index)
               << QString::number(cellsClass);
       strData.addRow(strList);
       strList.clear();
    }

  }
}

void PropDialog::on_listWidget_itemChanged(QListWidgetItem *item)
{
    on_listWidget_itemClicked(item);
}

void PropDialog::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    on_listWidget_itemClicked(current);
}

void PropDialog::setImgName(QString& s)
{
    this->imgName = s;
    imgName.truncate(8);
}

void PropDialog::setFileName(QString& s)
{
    this->fileName = s;
}

void PropDialog::setCellsClass(int cellClass)
{
    this->cellsClass = cellClass;
}

QString& PropDialog::getImgName()
{
    return imgName;
}

void PropDialog::calculateCellMask(QImage* mask, QImage* cellImage)
{
    Cluster clusters[3];
    clusters[0].green = 60;
    clusters[0].blue = 60; //nuclei
    clusters[1].green = 110;
    clusters[1].blue = 110; //citoplasm
    clusters[2].green = 173;
    clusters[2].blue = 173; //background
    clusters[0].nObjects = clusters[1].nObjects = clusters[2].nObjects = 0;

    Cluster newClusters[3];
    newClusters[0].green = newClusters[0].blue = 0;
    newClusters[1].green = newClusters[1].blue = 0;
    newClusters[2].green = newClusters[2].blue = 0;
    newClusters[0].nObjects = newClusters[1].nObjects = newClusters[2].nObjects = 0;
    double distance = 9999;

    Pixel pixMas[cellImage->width()][mask->height()];
    bool answer = true;

  while(answer){
    for(int i = 0; i < mask->width(); i++)
        for(int j =0;j < mask->height();j++){
            pixMas[i][j].green=QColor(mask->pixel(i,j)).green();
            pixMas[i][j].cl=0;
            pixMas[i][j].blue=QColor(mask->pixel(i,j)).red();
            for (int k = 0; k < 3; k++){
                if( qSqrt( ((pixMas[i][j].blue-clusters[k].blue)*(pixMas[i][j].blue-clusters[k].blue) + (pixMas[i][j].blue-clusters[k].blue)*(pixMas[i][j].blue-clusters[k].blue) )) < distance)
                    {
                        distance = qSqrt((pixMas[i][j].blue-clusters[k].blue)*(pixMas[i][j].blue-clusters[k].blue) + (pixMas[i][j].blue-clusters[k].blue)*(pixMas[i][j].blue-clusters[k].blue) );
                        pixMas[i][j].cl = k;
                    }
                }
                distance = 9999;
            }
            double blues[3] = {0.0,0.0,0.0};
            double greens[3] = {0.0,0.0,0.0};

            for(int i = 0; i < mask->width(); i++)
                for(int j = 0;j < mask->height();j++){
                    blues[pixMas[i][j].cl] += QColor(mask->pixel(i,j)).red();
                    greens[pixMas[i][j].cl] += QColor(mask->pixel(i,j)).green();
                    newClusters[pixMas[i][j].cl].nObjects++;
                }
            for(int i = 0; i < 3; i++){
                newClusters[i].blue = (int) (blues[i] / newClusters[i].nObjects);
                newClusters[i].green = (int) (greens[i] / newClusters[i].nObjects);
            }
  for(int i = 0; i < 3; i++)
     answer = answer && !((clusters[0].blue == newClusters[0].blue) && (clusters[0].green == newClusters[0].green));
  for(int i = 0; i < 3; i++){
      clusters[i]=newClusters[i];
      newClusters[i].nObjects = 0;
  }
  }
  for(int i = 0; i < mask->width(); i++)
      for(int j =0;j < mask->height();j++){
          mask->setPixel(i,j, qRgb((pixMas[i][j].cl+1)*50,(pixMas[i][j].cl+1)*50,(pixMas[i][j].cl+1)*50));
      }

  for(int i = 0; i < mask->width(); i++)
      for(int j =0;j < mask->height();j++){
          if((QColor(mask->pixel(i,j)).green() == 50) && !(QColor(cellImage->pixel(i,j)).green() > 0))
              mask->setPixel(i,j, qRgb(150,150,150));
          if((QColor(cellImage->pixel(i,j)).green() > 0))
              mask->setPixel(i,j, qRgb(50,50,50));
      }

}


void PropDialog::on_pushButton_3_clicked() //save
{
    QDir dir(path);
    QString path = "/out" + this->path;
    if(!QFile::exists(path)){
       dir.mkpath(path); //имя класса а не номер
    }
    if(fileName.isEmpty() || fileName.isNull())
    {
        QString filePath = QDir::currentPath() + path + "/" + "founded_props" +imgName + ".csv";
        QtCSV::Writer::write(filePath, strData);
    } else
    {
        QString filePath = QDir::currentPath() + path + "/" + fileName + ".csv";
        QtCSV::Writer::write(filePath, strData);
    }

}

void PropDialog::SetPath(QString path){
    this->path = path;
}

void PropDialog::on_radioButton_clicked() //ядро
{
    changeCellView();
}

void PropDialog::changeCellView()
{
    int index = ui->listWidget->currentRow();
    if(index > 0)
    {
        int color = props->at(index).color;
        int h = props->at(index).ur.Y - props->at(index).dl.Y;
        int w = props->at(index).ur.X - props->at(index).dl.X;
        QImage *cellNuclei = new QImage(w, h, img->format() );
        QImage *cellMask = new QImage(w, h, img->format() );
        QImage *mini_backg = new QImage(w, h, img->format() );
        QImage *cellCitoplasm = new QImage(w, h, img->format() );
        QImage *cellWithEverything = new QImage(w, h, img->format() );
        int x=0,y=0;
        int x1=props->at(index).ur.X;
        int y1=props->at(index).ur.Y;
        for(int i=props->at(index).dl.X; i<x1 ;i++) //imageSize.X-1
        {   for(int j=props->at(index).dl.Y; j<y1;j++)
              {
                int a=(QColor(dst->pixel(i,j)).green());
                if ((a==color))
                {
                  cellNuclei->setPixel(x,y,img->pixel(i,j));
                  cellWithEverything->setPixel(x,y,img->pixel(i,j));
                }
                else{
                    cellNuclei->setPixel(x,y,qRgb(0,0,0));
                    cellWithEverything->setPixel(x,y,img->pixel(i,j));
                    //mini1->setPixel(x,y,img->pixel(i,j));//
                    mini_backg->setPixel(x,y,img->pixel(i,j));
                }

                cellMask->setPixel(x,y,img->pixel(i,j));
                y++;
              }
            y=0;
            x++;
        }

        calculateCellMask(cellMask, cellNuclei);

        for(int i = 0; i < cellMask->width() ;i++) //imageSize.X-1
        {   for(int j = 0; j < cellMask->height();j++){
                if(QColor(cellMask->pixel(i,j)).green() == 100){
                    cellCitoplasm->setPixel(i,j,QColor(mini_backg->pixel(i,j)).rgb());
                }
                else
                    cellCitoplasm->setPixel(i,j, qRgb(0,0,0));
            }
        }

        if(ui->radioButton->isChecked())
        {
         my->setPixmap(QPixmap::fromImage(*cellNuclei));
        }
        if(ui->radioButton_2->isChecked())
        {
         my->setPixmap(QPixmap::fromImage(*cellCitoplasm));
        }
        if(ui->radioButton_3->isChecked())
        {
         my->setPixmap(QPixmap::fromImage(*cellMask));
        }
        if(ui->radioButton_4->isChecked())
        {
         my->setPixmap(QPixmap::fromImage(*cellWithEverything));
        }
        delete cellMask;
        delete cellCitoplasm;
        delete cellNuclei;
        delete cellWithEverything;
    }
}

void PropDialog::on_radioButton_2_clicked()
{
    changeCellView();
}

void PropDialog::on_radioButton_3_clicked()
{
    changeCellView();
}

void PropDialog::on_radioButton_4_clicked()
{
    changeCellView();
}

void PropDialog::calculateAndSaveParams()
{
    on_pushButton_2_clicked(); //рассчет параметров
    on_pushButton_3_clicked(); //сохранение параметров (можно задать имя файла на вкладке доп. чтобы сохранять в один файл
}
