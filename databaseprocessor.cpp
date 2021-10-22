#include "databaseprocessor.h"

DatabaseProcessor::DatabaseProcessor(QString location, QObject *parent) : QObject(parent)
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\med_db.db");
    db.open();

}

DatabaseProcessor::~DatabaseProcessor()
{

}

QVector<QStringList> DatabaseProcessor::getPatients(){
    QVector<QStringList> lst;
    QSqlQuery query;
    query.exec("SELECT * FROM patient");
    int i = 0;
    //Выводим значения из запроса
    while (query.next())
    {
        lst.append(QStringList());
        for(int j = 0 ; j < 7; j++)
            lst[i].append(query.value(j).toString());
        i++;
    }
    return lst;
}

QVector<QStringList> DatabaseProcessor::getMyelogram(int id){
    QVector<QStringList> lst;
    QSqlQuery query;
    query.prepare("SELECT myelogram.[blast_cells], myelogram.[monocytes], myelogram.[lymphocytes], myelogram.[sum_granulocytes], myelogram.erithroid_sum FROM study join myelogram on myelogram.id_study = study.id_study where study.id_study = ?");
    query.addBindValue(id);
    int i = 0;
    query.exec();
    //Выводим значения из запроса
    while (query.next())
    {
        lst.append(QStringList());
        for(int j = 0 ; j < 5; j++)
            lst[i].append(query.value(j).toString());
        i++;
    }
    return lst;
}

QVector<QStringList> DatabaseProcessor::getStudy(int id){
    QVector<QStringList> lst;
    QSqlQuery query;
    query.prepare("SELECT study.[id_study], study_type.[name], study.[date] FROM patient join study on study.id_patient = patient.id_patient join study_type on study_type.study_type_id = study.study_type where patient.id_patient = ?"); //id
    query.addBindValue(id);
    query.exec();
    int i = 0;
    //Выводим значения из запроса
    while (query.next())
    {
        lst.append(QStringList());
        for(int j = 0 ; j < 3; j++)
            lst[i].append(query.value(j).toString());
        i++;
    }
    return lst;
}


 void DatabaseProcessor::addMyelogram(QStringList values, int id_study){
     QSqlQuery query;
     query.prepare("INSERT INTO myelogram (blast_cells, monocytes, lymphocytes, sum_granulocytes, is_clinical, id_study) VALUES (?, ?, ?, ?, \"FALSE\", ?)"); //id
     for(int i = 0; i < 4; i++)
        query.addBindValue(values[i].toDouble());
     query.addBindValue(id_study);
     query.exec();
 }

QString DatabaseProcessor::getImagingLocation(int studyId){
    QSqlQuery query;
    query.prepare("SELECT atlant_imaging.location FROM study join atlant_imaging on study.id_study = atlant_imaging.id_study where study.id_study = ?"); //id
    query.addBindValue(studyId);
    query.exec();
    QString str;
    //Выводим значения из запроса
    while (query.next())
    {
        str = query.value(0).toString();
    }
    return str;
}
