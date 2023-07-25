#include "chatclient.h"

ChatClient::ChatClient(QWidget *parent)
    : QMainWindow(parent)
{
    
    
    ui.setupUi(this);
    
    client_tcp_ = new QTcpSocket(this);

    setWindowTitle("---聊天客户端，一杰第一版测试开发---");

    connect(client_tcp_, &QTcpSocket::readyRead, [=]() 
        {
            QByteArray recvMsg = client_tcp_->readAll();
            //TODO: 这里的服务器在后面要改成发送信息的另一个客户端的名字
            ui.recvMessagEdit->append("服务器say: " + recvMsg);
        });

    connect(client_tcp_, &QTcpSocket::connected, this, [=]()
        {
            ui.recvMessagEdit->append("恭喜，连接服务器成功!!!");
            ui.disconnect->setEnabled(true);
            ui.connect->setEnabled(false);
            //TODO: 连接成功按钮那里要加图片，连接成功是一个图片，在这里实现更换。连接失败又是另一个图片
        });

    connect(client_tcp_, &QTcpSocket::disconnected, this, [=]()
        {
            ui.recvMessagEdit->append("服务器已经断开连接了!!!");
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

    //连接服务器
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
