#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTextEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>

class QTcpServer;
class QTextEditor;
class QTcpSocket;

class MyServer: public QWidget {
    Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    QTextEdit* m_ptxt;
    quint16 m_NextBlockSize;
    quint16 m_nNextBlockSize;
    QImage *img;
private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);
public:
    MyServer(int nPort, QWidget* pwgt = 0);
    QImage* getImage();
public slots:
    void slotReadyReadImage();
    virtual void slotNewConnection();
            void slotReadClient();
signals:
     void imageRecieved();
};
