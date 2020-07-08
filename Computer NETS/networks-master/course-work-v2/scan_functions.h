#ifndef SCAN_FUNCTIONS_H
#define SCAN_FUNCTIONS_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QRunnable>
#include <QTimer>
#include <QEventLoop>
#include <QDebug>
#include "cross_sockets.h"

//1 - закрыт
//-1 - ошибка
//0 - открыт

class SimplePortScan : public QObject,public QRunnable{
    Q_OBJECT
    signals:
        void exit_code(int return_code,int port);
    public:
        int code = 0;
        explicit SimplePortScan(int port, QString address, QObject *parent = 0):QObject(parent),port(port),address(address){};
        void run(){
            //переписать под событийный таймер
            QTcpSocket socket;
            QTimer timer;
            timer.setSingleShot(true);
            QEventLoop loop;
            connect(&timer,&QTimer::timeout,&loop,&QEventLoop::quit);
            connect(&socket,&QAbstractSocket::connected,&loop,&QEventLoop::quit);
            socket.connectToHost(address,(qint16)port);
            timer.start(1500);
            loop.exec();
            if(timer.isActive()){
                    qDebug()<<port<<": open";
                    code = 0;
                    emit exit_code(code,port);
            }else{
                    qDebug()<<port<<": timeout";
                    code = 1;
                    emit exit_code(code,port);
            }

        };
    protected:
        int port;
        QString address;
};

class NonConnectPortScan : public QObject,public QRunnable{
    Q_OBJECT
    signals:
        void exit_code(int return_code,int port);
    public:
        explicit NonConnectPortScan(int port, QString address, QObject *parent = 0):QObject(parent),port(port),address(address){};
        void run(){
            emit exit_code(0,port);
        };
    protected:
        int port;
        QString address;
};
#endif // SCAN_FUNCTIONS_H
