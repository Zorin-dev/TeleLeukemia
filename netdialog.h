#ifndef NETDIALOG_H
#define NETDIALOG_H

#include <QDialog>
#include <QHostAddress>

namespace Ui {
class NetDialog;
}

class NetDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NetDialog(QWidget *parent = 0);
    ~NetDialog();
    void setAddr(QHostAddress addr);
    void setPort(int port);
    void setRemotePort(int rport);
    int getPort();
    QHostAddress getAddr();
    int getRemotePort();
private:
    Ui::NetDialog *ui;
    int port;
    int remotePort;
    QHostAddress addr;
signals:
   void apply();
private slots:
   void on_pushButton_clicked();
};

#endif // NETDIALOG_H
