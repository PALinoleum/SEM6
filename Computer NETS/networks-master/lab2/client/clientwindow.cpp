#include "clientwindow.h"

ClientWindow::ClientWindow(QWidget *parent) : QWidget(parent){
    //инициализация виджетов
    this->layout = new QVBoxLayout;
    this->startButtonsLayout = new QHBoxLayout;
    this->lMsgToServer = new QLabel("Сообщение для сервера");
    this->lFileName = new QLabel("Имя для полученного файла");
    this->eMsgToServer = new QLineEdit;
    this->eMsgToServer->setText("Клиент 1");
    this->eFileName = new QLineEdit;
    this->eFileName->setText("file.bin");
    this->startSPX = new QPushButton("Ожидание SPX сервера");
    this->startIPX = new QPushButton("Ожидание IPX сервера");

    //настройка layout-ов
    layout->addWidget(lMsgToServer);
    layout->addWidget(eMsgToServer);
    layout->addWidget(lFileName);
    layout->addWidget(eFileName);
        startButtonsLayout->addWidget(startSPX);
        startButtonsLayout->addWidget(startIPX);
    layout->addLayout(startButtonsLayout);
    this->setLayout(layout);
}

