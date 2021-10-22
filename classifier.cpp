#include "classifier.h"
#include "ui_classifier.h"
#include "propdialog.h"

int ClusterK::getElementsCount(){
    return this->elementsCount;
}
void ClusterK::setElementsCount(int count){
    this->elementsCount = count;
}
bool ClusterK::isNameEntered()
{
    return this->className != QString("не задано");
}

QString& ClusterK::getClassName(){
    return this->className;

}
void ClusterK::setClassName(QString& name){
    this->className = name;
}
double ClusterK::getRadius(){
    return this->radius;
}
void ClusterK::setRadius(double radius){
    this->radius = radius;
}
QVector<double>& ClusterK::getCentroid(){
    return this->centroid;
}
void ClusterK::setCentroid(QVector<double>& centroid){
    this->centroid = centroid;
}
void ClusterK::increaseElementsCount(){
    this->elementsCount++;
}
void ClusterK::clearCluster(){
    this->centroid.clear();
    this->elementsCount = 0;
    this->radius = 0;
    this->className.clear();
}
ClusterK::ClusterK(){
    this->elementsCount = 0;
    this->centroid = QVector<double>();
    this->radius = 0.0;
    this->className = "не задано";
    this->classNumber = 0;
}
ClusterK::ClusterK(const ClusterK& cluster){
    this->elementsCount = cluster.elementsCount;
    this->centroid = QVector<double>(); //cluster.centroid;
    foreach(double element, cluster.centroid){
        this->centroid.append(element);
    }
    this->radius = cluster.radius;
    this->className = cluster.className;
    this->classNumber = classNumber;
}
ClusterK::~ClusterK(){
    this->centroid.clear();
    this->elementsCount = 0;
    this->radius = 0;
    this->className.clear();
}
void ClusterK::setClassNumber(int classNumber){
    this->classNumber = classNumber;
}
int ClusterK::getClassNumber(){
    return this->classNumber;
}

Classifier::Classifier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Classifier)
{
    ui->setupUi(this);

    //ui->graphicsView->setScene(&sc);
    loc = new CellsLocation(this);
    //sc = new QGraphicsScene();
    my = new MyGraphicsItem(QPixmap());
    ui->graphicsView->setScene(&sc);
    sc.addItem(my);

    int nClusters = ui->lineEdit_2->text().toInt();
    clusters = QVector<ClusterK*>(nClusters);
    for (int i = 0;i < clusters.size(); i++) {
        clusters[i] = new ClusterK();
    }

    ui->tableWidget->horizontalHeader()->setResizeContentsPrecision(QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,120);
    ui->tableWidget->setColumnWidth(4,150);
    ui->tableWidget->setColumnWidth(5,90);
    ui->tableWidget->setColumnWidth(6,110);
    ui->tableWidget->setColumnWidth(7,45);
    ui->tableWidget->setColumnWidth(8,45);
    ui->tableWidget->setColumnWidth(9,45);
    ui->tableWidget->setColumnWidth(10,120);

    idStudy = 0;
    processor = NULL;
}

Classifier::~Classifier()
{
    delete ui;
}

void Classifier::updateTreeView()
{
    QStringList parameterLabels = strData.rowValues(0);

    ui->treeWidget->clear();

    ui->treeWidget->setColumnCount(1);
    QList<QTreeWidgetItem *> elements;

    QStringList imgNames;

    int imageNameIndex = parameterLabels.indexOf(PropDialog::IMAGE_NAME);

    QStringList row = strData.rowValues(1);
    QString str = row[imageNameIndex];
    imgNames.append(str);
    QString strNew;
    for(int i = 2; i < strData.rowCount(); i++){
        row = strData.rowValues(i);
        strNew = row[imageNameIndex];
        if(strNew != str){
            imgNames.append(str);
            str = strNew;
        }
    }

    QList<QTreeWidgetItem *> topleveItems;

    for (int i = 0; i < clusters.size(); ++i){
        QStringList names = QStringList();
        for(int i = 0; i < clusters.size(); i++)
        {
            auto name = clusters[i]->getClassName();
            if(!clusters[i]->isNameEntered())
                name = name + QString::number(i);
            names.append(name);
        }
        topleveItems.append(new QTreeWidgetItem((QTreeWidget*)0, names));
    }
        ui->treeWidget->insertTopLevelItems(0, topleveItems);
        QStringList paramsNames = strData.rowValues(0);
        int classIndex = paramsNames.indexOf(PropDialog::CELL_CLASS);
        int subImgIndex = paramsNames.indexOf(PropDialog::SUB_IMAGE_NUMBER);
        for(int k = 0; k < clusters.size(); k++)
        {
            for(int j = 1; j < strData.rowCount(); j++)
                if(strData.rowValues(j)[classIndex].toInt() == clusters[k]->getClassNumber())
                elements.append(new QTreeWidgetItem(topleveItems[k], QStringList(strData.rowValues(j)[imageNameIndex] + "-" + strData.rowValues(j)[subImgIndex]))); //12
      }
}

void Classifier::on_pushButton_clicked() //open file
{
    filePath = QFileDialog::getOpenFileNames();
    QtCSV::Reader::readToData(filePath[0], strData);

    QStringList parameterLabels = strData.rowValues(0);
    QListWidget* paramSelect = ui->clusteParamsSelect;
    QListWidgetItem* item = 0;
    QVector<ClusterK*>* temp = new QVector<ClusterK*>();
    double sumOfCentroidElements = 0;
    foreach(ClusterK* cluster, this->clusters)
    {
        auto clusterNew = new ClusterK(*cluster);
        temp->append(clusterNew);
        foreach(double element, clusterNew->getCentroid())
        {
            sumOfCentroidElements+=element;
        }
    }
    if(sumOfCentroidElements == 0)
    {
        propN.clear();
            for(int i = 0; i < parameterLabels.size(); ++i){ //делаем элементы с отметками
                paramSelect->addItem(parameterLabels.at(i));
                item = paramSelect->item(i);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // тут удаляются кластеры хз почему
                QString paramName = item->text();
                if(paramName == PropDialog::IMAGE_NAME || paramName == PropDialog::CELL_CLASS
                        || paramName == PropDialog::X_COORD_OF_CENTER || paramName == PropDialog::y_COORD_OF_CENTER
                        || paramName == PropDialog::SUB_IMAGE_NUMBER) //не участвуют в кластеризации
                {
                    item->setCheckState(Qt::Unchecked);
                } else
                {
                    item->setCheckState(Qt::Checked);
                    int paramIndex = parameterLabels.indexOf(paramName);
                    propN.append(paramIndex);
                    headers.append(parameterLabels[paramIndex]);
                }
            }
    }

        for(int i = 0; i < this->clusters.size(); i++)
        {
            this->clusters.at(i)->setCentroid(temp->at(i)->getCentroid());
        }
        delete temp;
        //this->clusters.clear();
        //foreach(ClusterK* cluster, *temp) // танцы с бубном чтобы сохранить внезапно удаляющиеся значения
        //{
        //   this->clusters.append(cluster);
       // }
    updateTreeView();
    updateClustersTable();
}

double Classifier::metric(QVector<double>* dataRow, QVector<double>* center){
    double sum = 0;
    for (int i = 0; i < propN.size(); i++)
        sum +=  coef[i] * ( ( (*dataRow)[propN[i]] - min[i]) / (max[i] - min[i]) - ( ( (*center)[i] - min[i]) / (max[i] - min[i]) )) * ( ((*dataRow)[propN[i]] - min[i]) / (max[i] - min[i]) - ((*center)[i] - min[i]) / (max[i] - min[i]) );
     return qSqrt(sum);
}

QVector<QVector<double>> Classifier::extractDataVector()
{
    QVector<double> tmp;
    QVector<QVector<double>> data;
    QStringList strlist;
    QStringList paramsNames = strData.rowValues(0);
    //int classIndex = paramsNames.indexOf(PropDialog::CELL_CLASS);
    for(int i = 1; i < strData.rowCount(); i++)
       {
            strlist = strData.rowValues(i);
            if(strlist.size() > 0)
            //tmp.append(strlist.at(classIndex).toInt()); //класс по умолчанию дожен быть 0
            for (int j = 0; j < strlist.size(); j++)
                tmp.append(strlist[j].toDouble());
            data.append(tmp);
            tmp.clear();
       }
    return data;
}

void Classifier::on_pushButton_2_clicked() //classif
{
    data = extractDataVector();

    for(int i = 0; i < propN.size()+1; i++)
    {
        max.append(0.0);
        min.append(99999.0);
    }
    for(int i = 0; i < propN.size(); i++)
        for(int j = 0; j < data.length(); j++)
        {
            if(data[j][propN[i]] > max[i])
                max[i] = data[j][propN[i]];
            if(data[j][propN[i]] < min[i])
                min[i] = data[j][propN[i]];
        }
    //вес параметра
//            coef.append(0);
//            coef.append(7);
//            coef.append(2);
//            coef.append(5);
//            coef.append(3);
//            coef.append(1);
//            coef.append(6);
//            coef.append(4);
    coef.append(1);
    coef.append(1);
    coef.append(1);
    coef.append(1);
    coef.append(1);
    coef.append(1);
    coef.append(1);
    coef.append(1);
          for(int i = coef.size()-1; i < propN.size(); i++){
              coef.append(1);
          }

  QVector<ClusterK*> newClusters = QVector<ClusterK*>(this->clusters.size());

  for (int i = 0; i < newClusters.size(); i++) {
      newClusters[i] = this->clusters[i];
  }

//   //Лимфоциты
//       clusters[0].centroid.append(0);
//       clusters[1].centroid.append(0);
//       clusters[2].centroid.append(0);
//       clusters[3].centroid.append(0);

//       clusters[0].centroid.append(8000.0);
//       clusters[0].centroid.append(9.0);
//       clusters[0].centroid.append(0.54);
//       clusters[0].centroid.append(1.4);
//       clusters[0].centroid.append(237.0);
//       clusters[0].centroid.append(33.0);
//       clusters[0].centroid.append(0.94);
//   //Нейтрофилы
//       clusters[1].centroid.append(5000.0);
//       clusters[1].centroid.append(0.0);
//       clusters[1].centroid.append(0.3);
//       clusters[1].centroid.append(1.7);
//       clusters[1].centroid.append(260.0);
//       clusters[1].centroid.append(38.0);
//       clusters[1].centroid.append(0.82);
//   //Пролимфоциты
//       clusters[2].centroid.append(13000.0);
//       clusters[2].centroid.append(7.0);
//       clusters[2].centroid.append(0.3);
//       clusters[2].centroid.append(1.7);
//       clusters[2].centroid.append(260.0);
//       clusters[2].centroid.append(38.0);
//       clusters[2].centroid.append(0.82);
//    //лимфобласты
//       clusters[3].centroid.append(15000.0);
//       clusters[3].centroid.append(7.0);
//       clusters[3].centroid.append(0.4);
//       clusters[3].centroid.append(1.5);
//       clusters[3].centroid.append(250.0);
//       clusters[3].centroid.append(54.0);
//       clusters[3].centroid.append(0.82);

       for (int i = 0; i < this->clusters.size(); i++ ){
           //clusters[i].nElements = 0;
           newClusters[i]->setElementsCount(0);
           if(!newClusters[i]->isNameEntered())
           {
               QString name = "класс";
               newClusters[i]->setClassName(name.append("-").append(i));
           }

           /*int ind = (int) data.length() * qrand()/RAND_MAX;
               clusters[i].centroid = data[ind];
               QVector<double> test = clusters[i].centroid;*///
        }
       QStringList paramsNames = strData.rowValues(0);
       int classIndex = paramsNames.indexOf(PropDialog::CELL_CLASS);
bool answer = true;
while(true){
   //приcваивание кластеров
   double minMetric = 999999.0;

   int cellClass = 0;
   for (int i = 0; i < data.size(); i++) {
       for(int clusterIndex = 0; clusterIndex < this->clusters.size(); clusterIndex++){
           double metric = Classifier::metric(&data[i], &clusters[clusterIndex]->getCentroid());
           if(metric < minMetric) { //if( (metric < minMetric) && (metric < clusters[clusterIndex]->getRadius()) )
                   minMetric = metric;
                   cellClass = clusterIndex;
                   clusters[clusterIndex]->increaseElementsCount();
           }
       }
       minMetric = 999999.0;
       data[i][classIndex] = cellClass;
   }
   if(answer == false)
       break;


   //рачет новых центров

   QVector<double> propVect = QVector<double>(propN.size());
   int count =0;

   for(int i = 0; i < this->clusters.size(); i++){
       for(int j = 0; j < data.size(); j++)
           if(data[j][classIndex] == i)
           {
               count++;
               for(int k = 0; k < propN.size(); k++)
                   propVect[k] += data[j][propN[k]];
           }
       if(count != 0)
       for(int k = 0; k < propN.size(); k++)
           propVect[k] /= count;
       newClusters[i]->setCentroid(propVect);
       count = 0;
       for(int k = 0; k < propN.size(); k++)
           propVect[k] = 0;
   }

   for(int i = 0; i < this->clusters.size(); i++)
       for(int j = 0; j < propN.size();j++)
           answer = !(!answer || (clusters[i]->getCentroid()[j] == newClusters[i]->getCentroid()[j]));

   this->clusters = QVector<ClusterK*>(newClusters.size());
   for (int i = 0 ; i < newClusters.size() ; i++ ) {
       this->clusters[i] = newClusters[i];
   }
 }

QFileInfo inf(filePath[0]);
QString filename;
QString path = inf.absolutePath();
QDir dir(path);

//переносим в папки

int imageNameIndex = paramsNames.indexOf(PropDialog::IMAGE_NAME);
int subImageIndex = paramsNames.indexOf(PropDialog::SUB_IMAGE_NUMBER);

for(int i = 1; i < data.size(); i++)
{
    QStringList dataRow = strData.rowValues(i);
    dataRow.replace(classIndex, QString::number(data[i-1][classIndex]));
    strData.replaceRow(i,dataRow);
    filename = strData.rowValues(i).value(imageNameIndex) + "-" + strData.rowValues(i).value(subImageIndex) + ".bmp";
    auto clusterName = clusters[data[i-1][classIndex]]->getClassName();
    QDir d(QString(path).remove("/out"));
    auto newImgPath = path + "/" + clusterName;
    if(!QFile::exists(newImgPath)){
       dir.mkpath(newImgPath); //имя класса а не номер
    }
    d.rename(filename, "out/" + clusterName + "/" + QString(filename).remove("out/"));
}

//QString filePath = QDir::currentPath() + "/" + "founded_props" +imgName + ".csv";
QFileInfo info (filePath[0]);
QtCSV::Writer::write(info.absolutePath() + "/classified.csv" , strData);
min.clear();
max.clear();
coef.clear();
data.clear();
//blast_cells, prolymphocytes, lymphocytes, sum_granulocytes, is_clinical, id_study
    QStringList lst;
    double amt = 0;
    for(int i = 0; i< this->clusters.size(); i++)
        amt += (double)(clusters[i]->getElementsCount());
    //lst.append(QString::number( (double)(clusters[2]->getElementsCount()) * 100 / amt));
    //lst.append(QString::number( (double)(clusters[3]->getElementsCount()) * 100 / amt)); //, clusters[0]->nElements,clusters[1]->nElements));
    //lst.append(QString::number( (double)(clusters[0]->getElementsCount()) * 100 / amt));
    //lst.append(QString::number( (double)(clusters[1]->getElementsCount()) * 100 / amt));
    //lst.append(QString("false"));
    //processor->addMyelogram(lst, this->idStudy);

    updateTreeView();
    updateClustersTable();
}

void Classifier::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    if(item->parent() != NULL){
    QString clazz = item->parent()->text(0);
    imgName = (item->text(0));
    QFileInfo fileInfo(filePath[0]);
    imgName = imgName + ".bmp"; // не маск
    auto path = fileInfo.dir().absolutePath() + "/" + clazz + "/" + QString(imgName).remove("out/");
    my->setPixmap(QPixmap(path));//
    imgPath = fileInfo.dir().absolutePath() + "/" + imgName + ".bmp";
    }

}

void Classifier::on_treeWidget_itemChanged(QTreeWidgetItem *item, int column)
{
    on_treeWidget_itemClicked(item, column);
}

void Classifier::on_treeWidget_itemEntered(QTreeWidgetItem *item, int column)
{
    on_treeWidget_itemClicked(item, column);
}

void Classifier::on_treeWidget_itemActivated(QTreeWidgetItem *item, int column)
{
    on_treeWidget_itemClicked(item, column);
}

void Classifier::on_treeWidget_itemPressed(QTreeWidgetItem *item, int column)
{
    on_treeWidget_itemClicked(item, column);
}

void Classifier::on_treeWidget_itemSelectionChanged()
{
    on_treeWidget_itemClicked(ui->treeWidget->currentItem(), 0);
}

void Classifier::on_pushButton_3_clicked()
{
    loc->setImgName(imgName);
    loc->setImgPath(imgPath);
    loc->setData(strData);
    loc->show();
    loc->showLocs();

}

void Classifier::on_pushButton_4_clicked() //задать
{
    int nClusters = ui->lineEdit_2->text().toInt();
    clusters = QVector<ClusterK*>(nClusters);
        for(int i = 0; i < nClusters; i++){
            clusters[i] = new ClusterK();
            clusters[i]->setElementsCount(0);
            clusters[i]->setClassNumber(i);
            for(int j = 0; j < propN.size() ;j++)
            {
                clusters[i]->getCentroid().append(ui->tableWidget->item(i, j)->text().toDouble());
            }
            int index = this->ui->tableWidget->columnCount() - 1;
            QString name = ui->tableWidget->item(i, index)->text().toUtf8();
            clusters[i]->setClassName(name);

            }
        updateClustersTable();
}

void Classifier::on_pushButton_5_clicked() //сгенерировать случайно
{
    int nClusters = ui->lineEdit_2->text().toInt();
    clusters = QVector<ClusterK*>(nClusters);
    if(data.length() != 0){
           for (int i = 0; i < nClusters; i++ ){
               clusters[i]->setElementsCount(0);
               //newClusters[i].nElements = 0;
               int ind = (int) data.length() * qrand()/RAND_MAX;
                   clusters[i]->getCentroid() = data[ind];
                   for(int j = 1; j < 8; j++){
                       QString text = QString::number((data[ind][j]));
                        ui->tableWidget->item(i, j-1)->setText(text);
                   }
                   //QVector<double> test = clusters[i].centroid;//
            }
    }
}

void Classifier::on_lineEdit_2_returnPressed()
{
    int nClusters = ui->lineEdit_2->text().toInt();
    clusters.clear();
    clusters = QVector<ClusterK*>(nClusters);
    for(int i = 0; i < nClusters; i++){
        clusters[i]->setElementsCount(0);
        clusters[i]->setClassNumber(i);
        clusters[i]->getCentroid().append(0);
        for(int j = 0; j < propN.size();j++)
            clusters[i]->getCentroid().append(ui->tableWidget->item(i, j)->text().toDouble());
        }
}

void Classifier::on_pushButton_6_clicked()
{
    int nClusters = ui->lineEdit_2->text().toInt();
    clusters.clear();
    clusters = QVector<ClusterK*>(nClusters);
    for(int i = 0; i < nClusters; i++){
        clusters[i]->setElementsCount(0);
        clusters[i]->setClassNumber(i);
        clusters[i]->getCentroid().append(0);
        for(int j = 0; j < propN.size();j++)
            clusters[i]->getCentroid().append(ui->tableWidget->item(i, j)->text().toDouble());
        }
}

void Classifier::setIdStudy(int id){
    idStudy = id;
}

void Classifier::setProcessor(DatabaseProcessor* processor){
    this->processor = processor;
}

void Classifier::setPath(QString path){
    this->path = path;
}

void Classifier::addColumn(QString header, int columnIndex)
{
    auto hitem = new QTableWidgetItem;
    hitem->setText(header);
    ui->tableWidget->setHorizontalHeaderItem(columnIndex, hitem);
    ui->tableWidget->model()->setHeaderData(columnIndex, Qt::Horizontal, header, Qt::DisplayRole);
}

void Classifier::updateClustersTable()
{
    auto table = ui->tableWidget;
    table->clear();
    table->setColumnCount(this->propN.size() + 4);

    for (auto col = 0; col < propN.size(); ++col) {
            auto text = headers[col];
            addColumn(text, col);
    }
    addColumn("R", propN.size());
    addColumn("G", propN.size()+1);
    addColumn("B", propN.size()+2);
    addColumn("Имя класса", propN.size()+3);

    auto classesCount = this->clusters.length();
    table->setRowCount(classesCount);
    for (auto r=0; r<classesCount; r++){
         for (auto c=0; c < propN.size(); c++)
         {
             double centroidElement=0;
             if(clusters[r]->getCentroid().size() > c )
             {
                centroidElement = this->clusters[r]->getCentroid()[c];
             }
             table->setItem( r, c, new QTableWidgetItem(QString::number(centroidElement)));
         }
         for (auto c=propN.size(); c < table->columnCount() - 1; c++) //раскрасшиваем классы случайным цветом
         {
             table->setItem( r, c, new QTableWidgetItem(QString::number((int) 255 * qrand()/RAND_MAX)));
         }
         table->setItem(r, table->columnCount() - 1, new QTableWidgetItem(this->clusters[r]->getClassName()));
    }
}

void Classifier::on_trainButton_clicked()
{
    QVector<QVector<double>> data = extractDataVector();
    QSet<int> clusterNumbers = QSet<int>();
    QStringList parameterLabels = strData.rowValues(0);
    int classIndex = parameterLabels.indexOf(PropDialog::CELL_CLASS);
    for (int i = 0; i < data.size(); i++)
    {
        int currentClass = data.at(i).at(classIndex);
        if(currentClass >= 0) //если задан класс
        {
            clusterNumbers.insert(currentClass);
        }
    }
    if(clusterNumbers.size() > 0) //начинаем обучение
    {
        QVector<ClusterK*> clusters = QVector<ClusterK*>();
        QSetIterator<int> iter(clusterNumbers);
        while (iter.hasNext())
        //инициализация кластеров
        {
            int classNumber = iter.next();
            ClusterK* cluster = new ClusterK();
            cluster->setClassNumber(classNumber);
            auto name = "класс" + QString::number(classNumber);
            cluster->setClassName(name);
            clusters.append(cluster);
        }

        QVector<double> classCenter = QVector<double>(this->propN.size());
        double classRadius = 0;
        int elementsCount = 0;

        for(int i = 0; i < clusters.size(); i++){
            for(int j = 0; j < data.size(); j++)
                if(data[j][classIndex] == clusters[i]->getClassNumber())
                {
                    elementsCount++;
                    for(int k = 0; k < propN.size(); k++)
                        classCenter[k] += data[j][propN.at(k)];
                }
            if(elementsCount != 0)
            for(int k = 0; k < propN.size(); k++)
                classCenter[k] /= elementsCount;
            clusters[i]->setCentroid(classCenter);
            clusters[i]->setRadius(classRadius);
            clusters[i]->setElementsCount(elementsCount);
            elementsCount = 0;
            for(int k = 0; k < propN.size(); k++)
                classCenter[k] = 0;
        }
        this->clusters = clusters;
    }
    updateClustersTable();
    updateTreeView();
    data.clear();
    ui->lineEdit_2->setText(QString::number(clusters.size()));
}

void Classifier::on_clusteParamsSelect_itemChanged(QListWidgetItem *item)
{
    if(item != NULL){
        QStringList parameterLabels = strData.rowValues(0);
        QListWidget* paramSelect = ui->clusteParamsSelect;
        QListWidgetItem* item = 0;
        propN.clear();
        headers.clear();
        for(int i = 0; i < paramSelect->count(); ++i){ //заполняем propN и заголовки таблицы
            item = paramSelect->item(i);
            QString paramName = item->text();
            auto checkState = item->checkState();
            if(checkState == Qt::Checked)
            {
                int paramIndex = parameterLabels.indexOf(paramName);
                propN.append(paramIndex);
                headers.append(parameterLabels[paramIndex]);
            }
        }
        for(int i = 0; i < clusters.size(); i++){
            auto newCentroid = QVector<double>(propN.size() + 1); //размер вектора признаков + класс
            clusters[i]->setCentroid(newCentroid);
        }
        this->data = extractDataVector();
        updateClustersTable();
    }
}
