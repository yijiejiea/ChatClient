#pragma once

#include <QtWidgets/QMainWindow>
#include <QtNetwork/qtcpsocket.h>
#include "ui_chatclient.h"

class ChatClient : public QMainWindow
{
    Q_OBJECT
   
     
public:
    ChatClient(QWidget *parent = nullptr);
    ~ChatClient();

private:
    //连接服务器
    void connect_button_clicked();

    //断开服务器连接
    void disconnect_button_clicked();

    //发送消息
    void send_message_button_clicked();
private:
    Ui::ChatClientClass ui;
    QTcpSocket* client_tcp_;
};
