#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <winsock2.h>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>

class ServerWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ServerWindow(QWidget *parent = 0);
    void OpenConnection();
private:
    QVBoxLayout *layout;
    QHBoxLayout *startButtonsLayout;
    QHBoxLayout *fileLayout;
    QLabel *lMsgToClient,*lFilePath;
    QLineEdit *eMsgToClient;
    QPushButton *startSPX,*startIPX,*changeFilePath;
signals:

public slots:
    struct sockaddr_ipx adress;
    void start_spx_transmit();
    void start_ipx_transmit();
};

#endif // SERVERWINDOW_H
