#ifndef CELLSLOCATION_H
#define CELLSLOCATION_H

#include <QDialog>
#include "include/qtcsv/stringdata.h"
#include <QGraphicsScene>
#include <QVector>
#include <QListWidgetItem>
#include "QtCore/qmath.h"

#include "mygraphicsobject.h"

namespace Ui {
class CellsLocation;
}

class CellsLocation : public QDialog
{
    Q_OBJECT

public:
    using QWidget::QObject;
    explicit CellsLocation(QWidget *parent = 0);
    ~CellsLocation();
    void setData(QtCSV::StringData data);
    void setImgPath(QString path);
    void showLocs();
    void drawLoc(QImage& img, int x, int y, QRgb color);
    void setImgName(QString path);

private slots:

    void on_graphic_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CellsLocation *ui;
    QString imgPath;
    QString imgName;
    QtCSV::StringData data;
    QGraphicsScene sc;
    MyGraphicsItem *my;
    QRgb colors[4];

};

#endif // CELLSLOCATION_H
