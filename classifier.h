#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include <QVector>
#include "include/qtcsv/reader.h"
#include "include/qtcsv/stringdata.h"
#include "include/qtcsv/writer.h"
#include "cellslocation.h"
#include "QtCore/qmath.h"
#include <QTreeWidgetItem>
#include <QGraphicsScene>
#include "mygraphicsobject.h"
#include "databaseprocessor.h"
#include <QPixmap>

namespace Ui {
class Classifier;
}

class ClusterK: public QObject
{
    Q_OBJECT
public:
    explicit ClusterK();
    explicit ClusterK(const ClusterK& cluster);
    ~ClusterK();
    int getElementsCount();
    void setElementsCount(int count);
    QString& getClassName();
    void setClassName(QString& name);
    double getRadius();
    void setRadius(double count);
    QVector<double>& getCentroid();
    void setCentroid(QVector<double>& centroid);
    void increaseElementsCount();
    void clearCluster();
    bool isNameEntered();
    void setClassNumber(int classNumber);
    int getClassNumber();
    //bool operator==(const ClusterK &other) const;

private:
    int classNumber;
    int elementsCount;
    QVector<double> centroid;
    QString className;
    double radius;
};

class Classifier : public QDialog
{
    Q_OBJECT
public:
    explicit Classifier(QWidget *parent = 0);
    ~Classifier();
    double metric(QVector<double> *from, QVector<double> *to);
    void setIdStudy(int id);
    void setProcessor(DatabaseProcessor* processor);
    QVector<int> propN;//номер параметра из файла (номер колонки), используемого для вектора признаков
    void setPath(QString path);

    void addColumn(QString header, int columnIndex);

    void updateTreeView();

    void updateClustersTable();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemChanged(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemEntered(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemActivated(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemPressed(QTreeWidgetItem *item, int column);

    void on_treeWidget_itemSelectionChanged();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_lineEdit_2_returnPressed();

    void on_pushButton_6_clicked();

    void on_trainButton_clicked();

    void on_clusteParamsSelect_itemChanged(QListWidgetItem *item);

private:
    Ui::Classifier *ui;
    QVector<ClusterK*> clusters;
    QStringList headers;
    QVector<double> max;
    QVector<double> min;
    QVector<int> coef;
    QVector<QVector<double>> data;
    QtCSV::StringData strData;
    QStringList filePath;
    QGraphicsScene sc;
    QString imgName;
    QString imgPath;
    CellsLocation* loc;
    MyGraphicsItem* my;
    int idStudy;
    DatabaseProcessor* processor;
    QString path;
    QVector<QVector<double>> extractDataVector();
};

#endif // CLASSIFIER_H
