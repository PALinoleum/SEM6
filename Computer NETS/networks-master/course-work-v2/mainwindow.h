#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QDebug>
#include <QThreadPool>
#include <QMutex>
#include <QRegExp>
#include <QRegExpValidator>

#include "scan_functions.h"

#define PORT_EDGE 1025
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //Список портов
    QMap<int,char> ports;
    bool scan_running = false;
    //0 - сканирование с соединением
    //1 - сканирование с без соединения
    char scan_mode = 0;
    int steps_completed = 0;
    QThreadPool threads;
    QMutex step_mutex,map_mutex;
private slots:
    void on_pushButton_clicked();

    void on_modeButton1_clicked();

    void on_modeButton2_clicked();

    void on_result_thread(int result_code,int port);

    void last_task_completed();
private:
    Ui::MainWindow *ui;
signals:
    void last_task();
};
#endif // MAINWINDOW_H
