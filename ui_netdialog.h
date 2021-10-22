/********************************************************************************
** Form generated from reading UI file 'netdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETDIALOG_H
#define UI_NETDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NetDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_3;

    void setupUi(QDialog *NetDialog)
    {
        if (NetDialog->objectName().isEmpty())
            NetDialog->setObjectName(QStringLiteral("NetDialog"));
        NetDialog->resize(665, 326);
        buttonBox = new QDialogButtonBox(NetDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(20, 270, 611, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        lineEdit = new QLineEdit(NetDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 120, 113, 20));
        lineEdit_3 = new QLineEdit(NetDialog);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(50, 220, 113, 20));
        lineEdit_4 = new QLineEdit(NetDialog);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(330, 220, 113, 20));
        label = new QLabel(NetDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 100, 91, 16));
        label_2 = new QLabel(NetDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(70, 200, 91, 16));
        pushButton = new QPushButton(NetDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(484, 230, 71, 23));
        label_3 = new QLabel(NetDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(370, 200, 47, 13));

        retranslateUi(NetDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NetDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NetDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(NetDialog);
    } // setupUi

    void retranslateUi(QDialog *NetDialog)
    {
        NetDialog->setWindowTitle(QApplication::translate("NetDialog", "\320\241\320\265\321\202\320\265\320\262\321\213\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("NetDialog", "127.0.0.1", Q_NULLPTR));
        lineEdit_3->setText(QApplication::translate("NetDialog", "2323", Q_NULLPTR));
        lineEdit_4->setText(QApplication::translate("NetDialog", "2323", Q_NULLPTR));
        label->setText(QApplication::translate("NetDialog", "IP \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("NetDialog", "\320\237\320\276\321\200\321\202 \320\260\320\261\320\276\320\275\320\265\320\275\321\202\320\260", Q_NULLPTR));
        pushButton->setText(QApplication::translate("NetDialog", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", Q_NULLPTR));
        label_3->setText(QApplication::translate("NetDialog", "\320\237\320\276\321\200\321\202", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NetDialog: public Ui_NetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETDIALOG_H
