#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QTimer>
#include <QtNetwork>
#include <QTextStream>


#include "../tmcsPi/ShareStruct.h"

namespace Ui {
class CSimuMW;
}

class CSimuMW : public QMainWindow
{
    Q_OBJECT

public:
    explicit CSimuMW(QWidget *parent = 0);
    ~CSimuMW();

protected:
    virtual void timerEvent(QTimerEvent *event);
    virtual void closeEvent(QCloseEvent *event);
private:
    QUdpSocket  *udp;

    CNodeInfo arrNI[6];
    CPCmd   pCmd;

private slots:
    void readPendingDatagrams();
    void on_btnStart_clicked();

    void on_btnClearLogs_clicked();

private:
    Ui::CSimuMW *ui;
};

#endif // MAINWINDOW_H
