#include "netdialog.h"
#include "ui_netdialog.h"
#include <QRegExpValidator>

NetDialog::NetDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetDialog)
{
    ui->setupUi(this);
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
        /* Создаем регулярное выражение с применением строки, как
         * повторяющегося элемента
         */
        QRegExp ipRegex ("^" + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange
                         + "\\." + ipRange + "$");
        /* Создаем Валидатор регулярного выражения с применением
         * созданного регулярного выражения
         */
        QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
        /* Устанавливаем Валидатор на QLineEdit */
        ui->lineEdit->setValidator(ipValidator);
}

NetDialog::~NetDialog()
{
    delete ui;
}

void NetDialog::on_pushButton_clicked()
{
    addr = QHostAddress(ui->lineEdit->text());
    remotePort = ui->lineEdit_3->text().toInt();
    port = ui->lineEdit_4->text().toInt();
    apply();
}

void NetDialog::setAddr(QHostAddress addr)
{
    this->addr = addr;
}

void NetDialog::setPort(int port)
{
    this->port = port;
}
void NetDialog::setRemotePort(int rport)
{
    this->remotePort = rport;
}
int NetDialog::getPort()
{
    return port;
}
QHostAddress NetDialog::getAddr()
{
    return addr;
}

int NetDialog::getRemotePort()
{
    return remotePort;
}
