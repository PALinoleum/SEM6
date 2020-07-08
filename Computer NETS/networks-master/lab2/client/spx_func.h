#ifndef SPX_FUNC_H
#define SPX_FUNC_H

#include <QWidget>
#include <QMessageBox>
#include <winsock2.h>
#include <wsipx.h>

int QT_WSAStartup(){
    WSADATA WSAData;
    if(!WSAStartup(MAKEWORD(2,2),&WSAData)){
        #ifdef QT_DEBUG
            QMessageBox msg;
            msg.setText("WinSock init success.");
            msg.exec();
        #endif
        return 0;
    }else{
            QMessageBox msg;
            msg.setText("WinSock init error.");
            msg.exec();
        return 1;
    }
}

#endif // SPX_FUNC_H
