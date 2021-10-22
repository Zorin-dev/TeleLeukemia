#include "cellslocation.h"
#include "ui_cellslocation.h"
#include "QPoint"
#include "mygraphicsobject.h"

CellsLocation::CellsLocation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CellsLocation)
{
    ui->setupUi(this);
    colors[0] = qRgb(230,10,230);
    colors[1] = qRgb(200,70,30);
    colors[2] = qRgb(100,200,160);
    colors[3] = qRgb(120,50,230);

    my = new MyGraphicsItem(QPixmap());

    QObject::connect(my, SIGNAL(MouseClicked()),this,SLOT(on_graphic_clicked()));

}

CellsLocation::~CellsLocation()
{
    delete ui;
}

void CellsLocation::setData(QtCSV::StringData data){
    this->data = data;
}

void CellsLocation::setImgPath(QString path){
    this->imgPath = path;
}

void CellsLocation::setImgName(QString name){
    this->imgName = name;
}

void CellsLocation::showLocs(){
    //super:show();
    //MyGraphicsItem* my = new MyGraphicsItem(QPixmap(imgPath));
    my->setPixmap(QPixmap(imgPath));
    ui->graphicsView->setScene(&sc);
    sc.addItem(my);

    QImage tmp = my->getImage();
        for(int i = 0; i < data.rowCount(); i++){
            QStringList lst = data.rowValues(i);
            int x = (lst[9].toInt());
            int y = (lst[10].toInt());
            int type = (lst[13].toInt());
            if(lst[11] == imgName){ //imgname
                if(type < 4)
                drawLoc(tmp, x, y, colors[type]);
                }// color of class
        }
        my->setPixmap(QPixmap::fromImage(tmp));
}

void CellsLocation::drawLoc(QImage& img, int x, int y, QRgb color){
    for(int i = 1;i < 4;i++)
        for(int j = -25; j < 25; j++)
            img.setPixel(x+j,y+i, color);
    for(int i = 1;i < 4;i++)
        for(int j = -25; j < 25; j++)
            img.setPixel(x+i,y+j, color);
}

void CellsLocation::on_graphic_clicked(){
    QPoint point = my->getPoint();
    int x = 0;
    int y = 0;
    int index = 0;
    double dist = 99999.0;
        for(int i = 0; i < data.rowCount(); i++){
            QStringList lst = data.rowValues(i);
            if(lst[11] == imgName){
                x = (lst[9].toInt());
                y = (lst[10].toInt());
                if( qSqrt((point.x()-x)*(point.x()-x) + (point.y()-y)*(point.y()-y)) < dist){
                    dist = qSqrt((point.x()-x)*(point.x()-x) + (point.y()-y)*(point.y()-y));
                    index = i;
                }
            }
        }
        QStringList lst = data.rowValues(index);


        ui->tableWidget->setColumnWidth(0,70);
        ui->tableWidget->setColumnWidth(1,150);
        ui->tableWidget->setColumnWidth(2,80);
        ui->tableWidget->setColumnWidth(3,120);
        ui->tableWidget->setColumnWidth(4,150);
        ui->tableWidget->setColumnWidth(5,90);
        ui->tableWidget->setColumnWidth(6,110);


        ui->tableWidget->item(0, 0)->setText(lst[1]);
        ui->tableWidget->item(0, 1)->setText(lst[3]);
        ui->tableWidget->item(0, 2)->setText(lst[4]);
        ui->tableWidget->item(0, 3)->setText(lst[5]);
        ui->tableWidget->item(0, 4)->setText(lst[6]);
        ui->tableWidget->item(0, 5)->setText(lst[7]);
        ui->tableWidget->item(0, 6)->setText(lst[8]);
        ui->tableWidget->item(0, 7)->setText(lst[13]);
        //twi->setText(lst[1]) ;


}

void CellsLocation::on_pushButton_clicked()
{
    ui->graphicsView->scale(1.1, 1.1);
}

void CellsLocation::on_pushButton_2_clicked()
{
    ui->graphicsView->scale(0.8, 0.8);
}
