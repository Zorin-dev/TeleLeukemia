/********************************************************************************
** Form generated from reading UI file 'cellslocation.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CELLSLOCATION_H
#define UI_CELLSLOCATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CellsLocation
{
public:
    QDialogButtonBox *buttonBox;
    QGraphicsView *graphicsView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;
    QPushButton *pushButton_3;
    QRadioButton *radioButton;

    void setupUi(QDialog *CellsLocation)
    {
        if (CellsLocation->objectName().isEmpty())
            CellsLocation->setObjectName(QStringLiteral("CellsLocation"));
        CellsLocation->resize(997, 593);
        buttonBox = new QDialogButtonBox(CellsLocation);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(910, 10, 70, 61));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        graphicsView = new QGraphicsView(CellsLocation);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 891, 341));
        pushButton = new QPushButton(CellsLocation);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(910, 300, 70, 23));
        pushButton_2 = new QPushButton(CellsLocation);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(910, 330, 70, 23));
        tableWidget = new QTableWidget(CellsLocation);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget->setItem(0, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget->setItem(0, 1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget->setItem(0, 2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget->setItem(0, 3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableWidget->setItem(0, 4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tableWidget->setItem(0, 5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tableWidget->setItem(0, 6, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tableWidget->setItem(0, 7, __qtablewidgetitem16);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 370, 891, 181));
        pushButton_3 = new QPushButton(CellsLocation);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(910, 390, 71, 23));
        radioButton = new QRadioButton(CellsLocation);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(910, 190, 82, 41));
        radioButton->setChecked(true);

        retranslateUi(CellsLocation);
        QObject::connect(buttonBox, SIGNAL(accepted()), CellsLocation, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CellsLocation, SLOT(reject()));

        QMetaObject::connectSlotsByName(CellsLocation);
    } // setupUi

    void retranslateUi(QDialog *CellsLocation)
    {
        CellsLocation->setWindowTitle(QApplication::translate("CellsLocation", "\320\240\320\260\321\201\320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \321\200\320\260\321\201\320\277\320\276\320\267\320\275\320\260\320\275\320\275\321\213\321\205 \320\272\320\273\320\265\321\202\320\276\320\272", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CellsLocation", "+", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CellsLocation", "-", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CellsLocation", "\320\237\320\273\320\276\321\211\320\260\320\264\321\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CellsLocation", "\320\246\320\270\321\202\320\276\320\277\320\273\320\260\320\267\320\274\320\260/\320\277\320\273\320\276\321\211\320\260\320\264\321\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CellsLocation", "\320\236\320\272\321\200\321\203\320\263\320\273\320\276\321\201\321\202\321\214", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("CellsLocation", "\320\232\320\276\321\215\321\204. \320\227\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("CellsLocation", "\320\236\321\202\321\202\320\265\320\275\320\276\320\272 \321\206\320\270\321\202\320\276\320\277\320\273\320\260\320\267\320\274\321\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("CellsLocation", "\320\257\321\200\320\272\320\276\321\201\321\202\321\214 \321\217\320\264\321\200\320\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("CellsLocation", "\320\234\320\276\320\274\320\265\320\275\321\202 \320\272\320\276\320\275\321\202\321\203\321\200\320\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("CellsLocation", "\320\242\320\270\320\277 \320\273\320\265\320\271\320\272\320\276\321\206\320\270\321\202\320\260", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem8->setText(QApplication::translate("CellsLocation", "1", Q_NULLPTR));

        const bool __sortingEnabled = tableWidget->isSortingEnabled();
        tableWidget->setSortingEnabled(false);
        tableWidget->setSortingEnabled(__sortingEnabled);

        pushButton_3->setText(QApplication::translate("CellsLocation", "\320\230\320\267\320\274. \321\202\320\270\320\277", Q_NULLPTR));
        radioButton->setText(QApplication::translate("CellsLocation", "\320\236\321\202\320\274\320\265\321\202\320\270\321\202\321\214 \n"
"\320\272\320\273\320\265\321\202\320\272\320\270", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CellsLocation: public Ui_CellsLocation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CELLSLOCATION_H
