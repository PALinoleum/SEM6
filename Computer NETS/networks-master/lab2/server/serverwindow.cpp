#include "serverwindow.h"

ServerWindow::ServerWindow(QWidget *parent) : QWidget(parent){
    //инициализация виджетов
    this->layout = new QVBoxLayout;
    this->startButtonsLayout = new QHBoxLayout;
    this->fileLayout = new QHBoxLayout;
    this->lMsgToClient = new QLabel("Сообщение для клиента");
    this->lFilePath = new QLabel("путь к файлу");
    this->eMsgToClient = new QLineEdit;
    this->eMsgToClient->setText("Сервер");
    this->startSPX = new QPushButton("Запуск SPX сервера");
    this->startIPX = new QPushButton("Запуск IPX сервера");
    this->changeFilePath = new QPushButton("Обзор");

    ZeroMemory(&adress, sizeof(SOCKADDR_IPX));
    adress.sa_family = AF_IPX;
    adress.sa_netnum = 0;
    adress.sa_nodenum = 0;
    adress.sa_socket = htons(5150);

    //настройка layout-ов
    layout->addWidget(lMsgToClient);
    layout->addWidget(eMsgToClient);
        fileLayout->addWidget(lFilePath);
        fileLayout->addWidget(changeFilePath);
    layout->addLayout(fileLayout);
        startButtonsLayout->addWidget(startSPX);
        startButtonsLayout->addWidget(startIPX);
    layout->addLayout(startButtonsLayout);
    this->setLayout(layout);
}

void ServerWindow::start_spx_transmit(){
    SOCKET server_socket;
    server_socket = socket(AF_IPX,SOCK_SEQPACKET,NSPROTO_SPX);
    bind(server_socket, &adress, sizeof(SOCKADDR_IPX));
    getsockname(server_socket, &adress, &addrlen);
};

void ServerWindow::start_ipx_transmit(){
    SOCKET server_socket;
    server_socket = socket(AF_IPX,SOCK_DGRAM,NSPROTO_IPX);
    bind(server_socket, &adress, sizeof(SOCKADDR_IPX));
    getsockname(server_socket, &adress, &addrlen);
};
