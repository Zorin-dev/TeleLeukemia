#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myserver.h"
#include "widget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    c = new Classifier(this);
    //UdpChat chat;
    net = new NetDialog(this);
    srv = new MyServer(2324,this);
    client = new MyClient("localhost", 2323);
    ui->verticalLayout_2->addWidget(client);
    ui->verticalLayout->addWidget(srv);
    connect(net, SIGNAL(apply()), this, SLOT(on_newParams()));
    connect(this, SIGNAL(imageReady()), client, SLOT(slotSendToServerImage()));
    connect(srv, SIGNAL(imageRecieved()), this, SLOT(onImageRecieved()));

    cellExtractAction = new QAction(QObject::tr("Сформировать выборку"), ui->tableWidget);
    cellClassifAction = new QAction(QObject::tr("Классификация и просмотр найденных клеток"), ui->tableWidget);
    ui->tableWidget->connect(cellExtractAction, SIGNAL(triggered()), this, SLOT(on_cellExtract()));
    ui->tableWidget->connect(cellClassifAction, SIGNAL(triggered()), this, SLOT(on_cellClassif()));

    processor = new DatabaseProcessor (" ", this);

    extractionWidget = new Widget();

    c->setProcessor(processor);

    ui->tableWidget->addAction(cellExtractAction);
    ui->tableWidget->addAction(cellClassifAction);
    ui->tableWidget->setContextMenuPolicy(Qt::ActionsContextMenu);

    QVector<QStringList> lst = processor->getPatients();

    ui->tableWidget_2->insertRow(1);
    for(int i =0 ;i< lst.length(); i++)
    {
        for(int j = 0; j < lst[i].length(); j++){
            QTableWidgetItem* it = new QTableWidgetItem(lst[i].value(j));
            ui->tableWidget_2->setItem(i,j, it);
        }
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_2_triggered()
{
    extractionWidget->show();
}

void MainWindow::on_action_triggered()
{

}

void MainWindow::on_newParams()
{
    disconnect(this, SIGNAL(imageReady()), client, SLOT(slotSendToServerImage()));
    delete client;
    delete srv;
    srv = new MyServer(net->getPort(), this);
    client = new MyClient(net->getAddr().toString(), net->getRemotePort());
    //client->setImage(new QImage("C:/zaharenko/TeleLeukemia/build/out000.bmp"));
    connect(this, SIGNAL(imageReady()), client, SLOT(slotSendToServerImage()));
    connect(srv, SIGNAL(imageRecieved()), this, SLOT(onImageRecieved()));
    ui->verticalLayout->addWidget(srv);
    ui->verticalLayout_2->addWidget(client);
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();

    QStringList filePathFewImage = QFileDialog::getOpenFileNames();

    pFiles = (QFileInfo(filePathFewImage[0]).absolutePath());

    foreach (QString file, filePathFewImage)
        ui->listWidget->addItem(QFileInfo(file).fileName());

}

void MainWindow::on_action_3_triggered()
{
    net->show();
}

void MainWindow::onImageRecieved()
{
    QPixmap pmp;
    pmp.convertFromImage(*srv->getImage());
    QGraphicsScene *sc = new QGraphicsScene;
    sc->addPixmap(pmp);
    ui->graphicsView->setScene(sc);
}

void MainWindow::on_pushButton_2_clicked()
{
    int index = ui->listWidget->currentRow();

    QImage* img = new QImage(pFiles + "/" +ui->listWidget->item(index)->text());

    client->setImage(img);

    imageReady();
}

void MainWindow::on_action_4_triggered()
{
    c->show();
}

void MainWindow::on_tableWidget_2_itemClicked(QTableWidgetItem *item)
{
   int row = item->row();
   //ui->tableWidget->rowCount()
   ui->tableWidget->clear();
   QStringList labels;
   labels.append("ID");
   labels.append("Тип");
   labels.append("Дата");
   ui->tableWidget->setHorizontalHeaderLabels(labels);

   QVector<QStringList> vect = processor->getStudy(ui->tableWidget_2->item(row,0)->text().toInt());
   if(ui->tableWidget->rowCount() < vect.length())
       for(int i = 0; i < vect.length() - ui->tableWidget->rowCount(); i++ )
            ui->tableWidget->insertRow(1);

     for( int i =0; i < vect.length(); i++){
        QTableWidgetItem* it = new QTableWidgetItem(vect[i].value(0));
        QTableWidgetItem* it1 = new QTableWidgetItem(vect[i].value(1));
        QTableWidgetItem* it2 = new QTableWidgetItem(vect[i].value(2));
        ui->tableWidget->setItem(i,0,it);
        ui->tableWidget->setItem(i,1,it1);
        ui->tableWidget->setItem(i,2,it2);
     }
}

void MainWindow::on_tableWidget_clicked(const QModelIndex &index)
{
 if(ui->tableWidget->item(index.row(), 0) != NULL)
     if(ui->tableWidget->item(index.row(), 1)->text() == QString("Миелограмма"))
    {

     // Сброс всех установок графика:
     QCPAbstractPlottable* fossils = ui->Myelogram->plottable(0);
     if(fossils != NULL) ui->Myelogram->removePlottable(fossils);
     fossils = ui->Myelogram->plottable(0);
     if(fossils!= NULL) ui->Myelogram->removePlottable(fossils);

    this->c->setIdStudy(ui->tableWidget->item(index.row(), 0)->text().toInt());
    ui->Myelogram->clearItems();
   //QCPBarsGroup* group = new QCPBarsGroup(ui->Myelogram);
   QCPBars* fossil = new QCPBars(ui->Myelogram->xAxis, ui->Myelogram->yAxis);
   QCPBars* fossil1 = new QCPBars(ui->Myelogram->xAxis, ui->Myelogram->yAxis);
   //group->append(fossil);
   //group->append(fossil1);
    fossil->setWidth(0.4);

    //ui->Myelogram
        QVector<QStringList> vec = processor->getMyelogram(ui->tableWidget->item(index.row(), 0)->text().toInt());
        ui->Myelogram->addPlottable(fossil);
        ui->Myelogram->addPlottable(fossil1);
        //ui->Myelogram->addPlottable(group);

        // Установки цвета:
        QPen pen;
        pen.setWidthF(1.5);//Толщина контура столбца
        fossil->setName(QString::fromUtf8("Клиническая миелограмма")); // Легенда
        pen.setColor(QColor(50, 50, 100));// Цвет контура столбца
        fossil->setPen(pen);
        // Цвет самого столбца, четвертый параметр - прозрачность
        fossil->setBrush(QColor(50, 50, 250, 70));

        fossil1->setName(QString::fromUtf8("Программная миелограмма")); // Легенда
        //pen.setColor(QColor(50, 50, 100));// Цвет контура столбца
        fossil->setPen(pen);
        // Цвет самого столбца, четвертый параметр - прозрачность
        fossil->setBrush(QColor(250, 50, 50, 70));

        // Установки значений оси X:
        QVector<double> ticks;
        QVector<QString> labels;
        ticks << 1 << 2 << 3 << 4 << 5 << 6;
        labels << "Бласт" << "Моноциты" << "Лимфоциты" << "Грунулоциты" << "Эритроидные";
        ui->Myelogram->xAxis->setAutoTicks(false);
        ui->Myelogram->xAxis->setAutoTickLabels(false);
        ui->Myelogram->xAxis->setTickVector(ticks);
        ui->Myelogram->xAxis->setTickVectorLabels(labels);
        ui->Myelogram->xAxis->setSubTickCount(0);
        ui->Myelogram->xAxis->setTickLength(0, 4);
        ui->Myelogram->xAxis->grid()->setVisible(true);
        ui->Myelogram->xAxis->setRange(0, 6);

        // Установки значений оси Y:
        ui->Myelogram->yAxis->setRange(0, 100);
        ui->Myelogram->yAxis->setPadding(5);
        ui->Myelogram->yAxis->setLabel(QString::fromUtf8("Процент"));
        ui->Myelogram->yAxis->grid()->setSubGridVisible(true);
        QPen gridPen;
        gridPen.setStyle(Qt::SolidLine);
        gridPen.setColor(QColor(0, 0, 0, 25));
        ui->Myelogram->yAxis->grid()->setPen(gridPen);
        gridPen.setStyle(Qt::DotLine);
        ui->Myelogram->yAxis->grid()->setSubGridPen(gridPen);


        // Данные:
        QVector<double> fossilData;
        QVector<double> fossil1Data;
        //qsrand (time(NULL));
//        fossilData  << qrand() % 10 + 2.5
//                    << qrand() % 10 + 2.5
//                    << qrand() % 10 + 2.5
//                    << qrand() % 10 + 2.5
//                    << qrand() % 10 + 2.5
//                    << qrand() % 10 + 2.5
//                    << qrand() % 10 + 2.5;
        for(int i = 0; i < vec[0].length(); i++)
            fossilData  << vec[0].value(i).toDouble();
        for(int i = 0; i < vec.last().length(); i++)
            fossil1Data  << vec.last().value(i).toDouble();
        fossil->setData(ticks, fossilData);
        fossil1->setData(ticks, fossil1Data);

        // Легенда:
        ui->Myelogram->legend->setVisible(true);
        ui->Myelogram->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        ui->Myelogram->legend->setBrush(QColor(255, 255, 255, 200));
        QPen legendPen;
        legendPen.setColor(QColor(130, 130, 130, 200));
        ui->Myelogram->legend->setBorderPen(legendPen);
        QFont legendFont = font();
        legendFont.setPointSize(10);
        ui->Myelogram->legend->setFont(legendFont);
        ui->Myelogram->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
        ui->Myelogram->replot();


    }
}

void MainWindow::on_cellExtract(){

    int currentRow = ui->tableWidget->currentRow();

    QTableWidgetItem* it = ui->tableWidget->item(currentRow, 0);
    if(it != NULL)
        if(it->text() != QString())
        {
            QString path =  processor->getImagingLocation(it->text().toInt());
            extractionWidget->setPathToPdlg(path);
            extractionWidget->setWindowTitle(QString("Пациент ") + ui->tableWidget_2->item(ui->tableWidget_2->currentRow(), 1)->text() + " Мазок пунктата костного мозга. Подозрение на острый лимфобластный лейкоз");
            extractionWidget->show();
        }

}

void MainWindow::on_cellClassif(){

    int currentRow = ui->tableWidget->currentRow();

    QTableWidgetItem* it = ui->tableWidget->item(currentRow, 0);
    if(it != NULL)
        if(it->text() != QString())
        {
            c->setWindowTitle(QString("Пациент ") + ui->tableWidget_2->item(ui->tableWidget_2->currentRow(), 1)->text() + " Мазок пунктата костного мозга. Подозрение на острый лимфобластный лейкоз");
            c->show();
        }
}
