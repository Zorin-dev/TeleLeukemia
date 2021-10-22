#ifndef PROPDIALOG_H
#define PROPDIALOG_H

#include <QDialog>
#include "cellparams.h"
#include "mygraphicsobject.h"
#include "QtCore/qmath.h"
#include "include/qtcsv/reader.h"
#include "include/qtcsv/stringdata.h"
#include "include/qtcsv/writer.h"

enum PixelClass{ NONE, BCG , CPL , NCL };

namespace Ui {
class PropDialog;
}

struct Pixel{
    int cl;
    int green;
    int blue;
};

struct Cluster{
    int green;
    int blue;
    int nObjects;
};

class PropDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PropDialog(QWidget *parent = 0, QImage* img=NULL, QImage *dst=NULL);
    ~PropDialog();
    void setProps(QVector<CellProps> * pr);
    void clear();
    void setImage(QImage& src);
    QPushButton* getButton();
    QImage* getImage();
    void setDst(QImage &dst);
    QImage* getDst();
    void setImgName(QString &s);
    void setFileName(QString &s);
    QString& getImgName();
    void calculateCellMask(QImage* img, QImage *mask);
    void SetPath(QString path);
    void calculateAndSaveParams();
    void setCellsClass(int cellClass);

    QStringList strList;
    QtCSV::StringData strData;

    static const QString PERIMETER; //"Perimeter"
    static const QString SQUARE; //"S"
    static const QString SHAPE;
    static const QString CITOPLASM_RATIO;
    static const QString ROUNDNESS;
    static const QString RECTANGLE_FILL;
    static const QString CITOPLASM_HUE;
    static const QString NUCLEAR_BRIGHTNESS;
    static const QString CONTOUR_MOMENT;
    static const QString X_COORD_OF_CENTER;
    static const QString y_COORD_OF_CENTER;
    static const QString IMAGE_NAME;
    static const QString SUB_IMAGE_NUMBER;
    static const QString CELL_CLASS;

private:
    void changeCellView();
signals:
    void PressSgn();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_pushButton_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

private:
    Ui::PropDialog *ui;
    QVector<CellProps> *props;
    QImage* img;
    QImage*  dst;
    QGraphicsScene sc;
    MyGraphicsItem *my;
    QString imgName;
    QString fileName;
    QImage* mini;
    QString path;
    int cellsClass;
};

#endif // PROPDIALOG_H
