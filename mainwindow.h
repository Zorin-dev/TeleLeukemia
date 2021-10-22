#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "netdialog.h"
#include "myserver.h"
#include "myclient.h"
#include "classifier.h"
#include <QFileDialog>
#include "databaseprocessor.h"
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_2_triggered();

    void on_action_triggered();

    void on_pushButton_clicked();

    void on_newParams();

    void on_action_3_triggered();

    void on_pushButton_2_clicked();

    void onImageRecieved();

    void on_action_4_triggered();

    void on_tableWidget_2_itemClicked(QTableWidgetItem *item);

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_cellExtract();

    void on_cellClassif();

private:
    Ui::MainWindow *ui;
    NetDialog* net;
    MyServer* srv;
    MyClient* client;
    Classifier* c;
    DatabaseProcessor* processor;
    QString pFiles;
    QAction* cellExtractAction;
    QAction* cellClassifAction;
    Widget* extractionWidget;
signals:
    void imageReady();
};

#endif // MAINWINDOW_H
