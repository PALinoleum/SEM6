#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cross_sockets.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QRegExp *re = new QRegExp("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    QRegExpValidator *validator = new QRegExpValidator(*re);
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(PORT_EDGE);
    ui->modeButton1->hide();
    ui->modeButton2->hide();
    ui->addressLine->setValidator(validator);
    this->steps_completed = 0;
    this->threads.setMaxThreadCount(128);
    connect(this,SIGNAL(last_task()),SLOT(last_task_completed()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
   if(scan_running){
        this->scan_running= false;
       this->ui->pushButton->setText("Сканировать");
       this->ui->modeButton1->setEnabled(true);
       this->ui->modeButton2->setEnabled(true);
       this->ui->addressLine->setEnabled(true);
       this->ui->progressBar->hide();
       this->threads.clear();
       qDebug()<<"Сканирование остановлено\n";
   }else{
       this->scan_running = true;

       this->ui->pushButton->setText("Отменить");
       this->ui->modeButton1->setEnabled(false);
       this->ui->modeButton2->setEnabled(false);
       this->ui->addressLine->setEnabled(false);

       this->ui->progressBar->show();
       this->ui->progressBar->reset();

       this->steps_completed = 0;
       this->ports.clear();
       this->ui->listWidget->addItem("Сканирование запущено.");
       this->ui->listWidget->addItem(QString("Сканируемый адрес: ")+this->ui->addressLine->text());

       qDebug()<<"Сканирование запущено\n";
       qDebug()<<"Режим: "<<(int)this->scan_mode<<"\n";

       for(int i = 0;i<PORT_EDGE;i++){
           if(scan_running){
            SimplePortScan *scan_thread = new SimplePortScan(i,ui->addressLine->text());
            connect(scan_thread,SIGNAL(exit_code(int,int)),SLOT(on_result_thread(int,int)));
            this->threads.start(scan_thread);
           }
       };

   }
}


void MainWindow::on_modeButton1_clicked()
{
    this->scan_mode=0;
}

void MainWindow::on_modeButton2_clicked()
{
    this->scan_mode=1;
}

void MainWindow::on_result_thread(int result_code,int port)
{
    this->step_mutex.lock();
    this->steps_completed++;
    this->ui->progressBar->setValue(this->steps_completed);
    if(steps_completed==this->ui->progressBar->maximum()){
        emit last_task();
    }
    this->step_mutex.unlock();

    this->map_mutex.lock();
    this->ports.insert(port,(int)result_code);
    this->map_mutex.unlock();

};

void MainWindow::last_task_completed(){
    this->ui->listWidget->addItem("Сканирование завершено.");
    for(int i = 0;i<PORT_EDGE;i++){
        if(this->ports[i]==0) {
            this->ui->listWidget->addItem(QString::number(i)+QString(": порт открыт."));
        }
    }
    this->scan_running= false;
    this->ui->pushButton->setText("Сканировать");
    this->ui->modeButton1->setEnabled(true);
    this->ui->modeButton2->setEnabled(true);
    this->ui->addressLine->setEnabled(true);
    this->ui->progressBar->hide();
    this->ui->listWidget->addItem("");
};
