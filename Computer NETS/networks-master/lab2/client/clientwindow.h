#ifndef CLIENTWINDOW_H
#define CLIENTWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QLabel>

class ClientWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ClientWindow(QWidget *parent = 0);

private:
    QVBoxLayout *layout;
    QHBoxLayout *startButtonsLayout;
    QLabel *lMsgToServer,*lFileName;
    QLineEdit *eMsgToServer,*eFileName;
    QPushButton *startSPX,*startIPX;
signals:

public slots:
};

#endif // CLIENTWINDOW_H
