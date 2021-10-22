/********************************************************************************
** Form generated from reading UI file 'propdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPDIALOG_H
#define UI_PROPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PropDialog
{
public:
    QDialogButtonBox *buttonBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QListWidget *listWidget;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QGraphicsView *graphicsView;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QPushButton *pushButton_3;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;

    void setupUi(QDialog *PropDialog)
    {
        if (PropDialog->objectName().isEmpty())
            PropDialog->setObjectName(QStringLiteral("PropDialog"));
        PropDialog->resize(608, 426);
        buttonBox = new QDialogButtonBox(PropDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(510, 20, 81, 31));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        scrollArea = new QScrollArea(PropDialog);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 30, 51, 211));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 49, 209));
        listWidget = new QListWidget(scrollAreaWidgetContents);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 51, 211));
        scrollArea->setWidget(scrollAreaWidgetContents);
        lineEdit = new QLineEdit(PropDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(480, 100, 113, 20));
        lineEdit_2 = new QLineEdit(PropDialog);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(480, 120, 113, 20));
        lineEdit_5 = new QLineEdit(PropDialog);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(480, 140, 113, 20));
        label = new QLabel(PropDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(420, 100, 47, 13));
        label_2 = new QLabel(PropDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(420, 120, 47, 13));
        label_5 = new QLabel(PropDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(420, 140, 47, 13));
        pushButton = new QPushButton(PropDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(510, 60, 81, 23));
        pushButton_2 = new QPushButton(PropDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(410, 60, 91, 23));
        graphicsView = new QGraphicsView(PropDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(100, 30, 301, 211));
        label_7 = new QLabel(PropDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(40, 10, 47, 13));
        label_8 = new QLabel(PropDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(220, 0, 81, 21));
        lineEdit_3 = new QLineEdit(PropDialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(480, 160, 113, 20));
        label_3 = new QLabel(PropDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(410, 160, 61, 20));
        pushButton_3 = new QPushButton(PropDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(410, 30, 91, 21));
        radioButton = new QRadioButton(PropDialog);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setEnabled(true);
        radioButton->setGeometry(QRect(420, 190, 97, 21));
        radioButton->setAcceptDrops(false);
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(PropDialog);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(420, 220, 97, 20));
        radioButton_3 = new QRadioButton(PropDialog);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(420, 250, 97, 20));
        radioButton_4 = new QRadioButton(PropDialog);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(420, 280, 151, 20));

        retranslateUi(PropDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), PropDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PropDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(PropDialog);
    } // setupUi

    void retranslateUi(QDialog *PropDialog)
    {
        PropDialog->setWindowTitle(QApplication::translate("PropDialog", "\320\235\320\260\320\271\320\264\320\265\320\275\320\275\321\213\320\265 \320\276\320\261\321\212\320\265\320\272\321\202\321\213", Q_NULLPTR));
        label->setText(QApplication::translate("PropDialog", "XC", Q_NULLPTR));
        label_2->setText(QApplication::translate("PropDialog", "YC", Q_NULLPTR));
        label_5->setText(QApplication::translate("PropDialog", "S", Q_NULLPTR));
        pushButton->setText(QApplication::translate("PropDialog", "\320\232\320\276\320\275\321\202\321\203\321\200", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("PropDialog", "\320\230\320\267\320\262\320\273\320\265\321\207\321\214 \320\262\321\201\320\265", Q_NULLPTR));
        label_7->setText(QApplication::translate("PropDialog", "\342\204\226", Q_NULLPTR));
        label_8->setText(QApplication::translate("PropDialog", "\320\236\320\261\321\212\320\265\320\272\321\202", Q_NULLPTR));
        label_3->setText(QApplication::translate("PropDialog", "ShapeCoeff", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("PropDialog", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", Q_NULLPTR));
        radioButton->setText(QApplication::translate("PropDialog", "\320\257\320\264\321\200\320\276", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("PropDialog", "\320\246\320\270\321\202\320\276\320\277\320\273\320\260\320\267\320\274\320\260", Q_NULLPTR));
        radioButton_3->setText(QApplication::translate("PropDialog", "\320\234\320\260\321\201\320\272\320\260", Q_NULLPTR));
        radioButton_4->setText(QApplication::translate("PropDialog", "\320\237\320\276\320\273\320\275\321\213\320\271 \321\204\321\200\320\260\320\263\320\274\320\265\320\275\321\202", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PropDialog: public Ui_PropDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPDIALOG_H
