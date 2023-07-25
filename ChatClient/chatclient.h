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
    //���ӷ�����
    void connect_button_clicked();

    //�Ͽ�����������
    void disconnect_button_clicked();

    //������Ϣ
    void send_message_button_clicked();
private:
    Ui::ChatClientClass ui;
    QTcpSocket* client_tcp_;
};
