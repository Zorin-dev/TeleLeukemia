#include "myclient.h"

MyClient::MyClient(const QString& strHost, int nPort, QWidget* pwgt): QWidget(pwgt), m_nNextBlockSize(0)
{
    m_pTcpSocket = new QTcpSocket(this);

    m_pTcpSocket->connectToHost(strHost,nPort);
    connect(m_pTcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(m_pTcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(m_pTcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(slotError(QAbstractSocket::SocketError)));

    m_ptxtInfo = new QTextEdit();
    m_ptxtInput = new QLineEdit();

    img = new QImage();

    m_ptxtInfo->setReadOnly(true);
    QPushButton* pcmd = new QPushButton("&Send");
    connect(pcmd, SIGNAL(clicked()), SLOT(slotSendToServer()));
    connect(m_ptxtInput, SIGNAL(returnPressed()),this, SLOT(slotSendToServer()));

    QVBoxLayout* pvbxLayout = new QVBoxLayout();
    //pvbxLayout->addWidget(new QLabel("<H1>Поле отправки</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);
    setLayout(pvbxLayout);
}


void MyClient::slotReadyRead()
{
    QDataStream in(m_pTcpSocket);
    in.setVersion(QDataStream::Qt_5_3);
    for(;;) {
        if(!m_nNextBlockSize) {
            if (m_pTcpSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

    if (m_pTcpSocket->bytesAvailable() < m_nNextBlockSize) {
        break;
    }
    QTime time;
    QString str;
    in>>time>>str;
    m_ptxtInfo->append(time.toString() + "" + str);
    m_nNextBlockSize = 0;
    }
}
void MyClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError = "Error";
    m_ptxtInfo->append(strError);
}

void MyClient::slotSendToServer()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_3);
    out << quint16(0) << quint16(1) << QTime::currentTime() << m_ptxtInput->text();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    m_pTcpSocket->write(arrBlock);
    m_ptxtInput->setText("");

}

void MyClient::slotConnected()
{
    m_ptxtInfo->append("Recieved the connected() signal");
}


void MyClient::slotSendToServerImage()
{
//qDebug() « "Client Send image";
    QByteArray arrBlock;
    //arrBlock = "Test_Server_arrBlock";
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);
    out << quint16(0) << quint16(2) << *img;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    m_pTcpSocket->write(arrBlock);
}
void MyClient::setImage(QImage* img){
    this->img=img;
}

MyClient::~MyClient()
{

}

