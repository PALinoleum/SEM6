#include <QtWidgets>
#include "spx_func.h"
#include "clientwindow.h"

int main(int argc, char *argv[]){
    QApplication app(argc,argv);
    if(QT_WSAStartup()) return 1;
    ClientWindow *window = new ClientWindow;
    window->show();
    return app.exec();
}
