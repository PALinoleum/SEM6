#include <winsock2.h>
#include <QtWidgets>
#include "spx_func.h"
#include "serverwindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc,argv);
    if(QT_WSAStartup()) return 1;
    ServerWindow *window = new ServerWindow;
    window->show();
    return app.exec();
}
