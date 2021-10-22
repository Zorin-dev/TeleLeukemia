#ifndef DATABASEPROCESSOR_H
#define DATABASEPROCESSOR_H

#include <QObject>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include <QStringList>
#include <QVariant>
#include <QVector>
#include <QTableWidgetItem>

class DatabaseProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseProcessor(QString location, QObject *parent = 0);
    ~DatabaseProcessor();
    QVector<QStringList> getPatients();
    QVector<QStringList> getMyelogram(int id);
    QVector<QStringList> getStudy(int id);
    QString getImagingLocation(int studyId);
    void addMyelogram(QStringList values, int id_study);

signals:

public slots:

private:
    QSqlDatabase db;
};

#endif // DATABASEPROCESSOR_H
