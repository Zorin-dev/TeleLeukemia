#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>
#include <QFile>

//class QTextEdit;
//class QLineEdit;

class MyClient : public QWidget
{
Q_OBJECT
private:
    QImage* img;
    QTcpSocket* m_pTcpSocket;
    QTextEdit* m_ptxtInfo;
    QLineEdit* m_ptxtInput;
    quint16 m_nextBlockSize;
    quint16 m_nNextBlockSize;
    const int SIZE_BLOCK_FOR_SEND_FILE = 256;

public:
   void setImage(QImage* img);
    MyClient(const QString& strHost, int nPort, QWidget* pwgt = 0);
    ~MyClient();


private slots:
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError err);
    void slotSendToServer();
    void slotConnected();
    void slotSendToServerImage();
};

