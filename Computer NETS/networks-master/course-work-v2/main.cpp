#include "mainwindow.h"

#include <QApplication>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Сканер портов");
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("ВНИМАНИЕ");
    msgBox.setText("Программа создана исключительно в образовательных целях.\nБольшинство интернет-провайдеров прямо запрещают сканирование портов. Используйте программу исключительно в локальных сетях.");
    msgBox.exec();
    w.show();
    return a.exec();
}
