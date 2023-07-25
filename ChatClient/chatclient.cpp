#include "chatclient.h"

ChatClient::ChatClient(QWidget *parent)
    : QMainWindow(parent)
{
    
    
    ui.setupUi(this);
    
    client_tcp_ = new QTcpSocket(this);

    setWindowTitle("---����ͻ��ˣ�һ�ܵ�һ����Կ���---");

    connect(client_tcp_, &QTcpSocket::readyRead, [=]() 
        {
            QByteArray recvMsg = client_tcp_->readAll();
            //TODO: ����ķ������ں���Ҫ�ĳɷ�����Ϣ����һ���ͻ��˵�����
            ui.recvMessagEdit->append("������say: " + recvMsg);
        });

    connect(client_tcp_, &QTcpSocket::connected, this, [=]()
        {
            ui.recvMessagEdit->append("��ϲ�����ӷ������ɹ�!!!");
            ui.disconnect->setEnabled(true);
            ui.connect->setEnabled(false);
            //TODO: ���ӳɹ���ť����Ҫ��ͼƬ�����ӳɹ���һ��ͼƬ��������ʵ�ָ���������ʧ��������һ��ͼƬ
        });

    connect(client_tcp_, &QTcpSocket::disconnected, this, [=]()
        {
            ui.recvMessagEdit->append("�������Ѿ��Ͽ�������!!!");
            ui.disconnect->setEnabled(false);
            ui.connect->setEnabled(true);
        });

    connect(ui.connect, &QPushButton::clicked, this, &ChatClient::connect_button_clicked);
}

ChatClient::~ChatClient()
{}

void ChatClient::connect_button_clicked()
{
    QString ip = ui.ip->text();
    unsigned short port = ui.port->text().toInt();

    //���ӷ�����
    client_tcp_->connectToHost(QHostAddress(ip), port);
    ui.disconnect->setEnabled(true);
    ui.connect->setEnabled(false);
}

void ChatClient::disconnect_button_clicked()
{
    client_tcp_->close();
    ui.disconnect->setEnabled(false);
    ui.connect->setEnabled(true);
}

void ChatClient::send_message_button_clicked()
{
    QString sendMsg = ui.sendMessageEdit->toPlainText();
    client_tcp_->write(sendMsg.toUtf8());
}
