#include "simumw.h"
#include "ui_simumw.h"




CSimuMW::CSimuMW(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CSimuMW)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("NDTC");
    QCoreApplication::setOrganizationDomain("ndtc.com");
    QCoreApplication::setApplicationName("tmcsSimu");
    QSettings::setDefaultFormat( QSettings::IniFormat );
    QSettings settings;
    if( settings.contains("geometry") ){
        restoreGeometry(settings.value("geometry").toByteArray());
    }
    if( settings.contains("windowState") ){
        restoreState(settings.value("geometry").toByteArray());
    }


    for( int i=0;i<6;i++ ){
        arrNI[i].setID(i);

        arrNI[i].simuT0();

    }

    udp = new QUdpSocket(this);

    udp->bind(50002);

    connect( udp,SIGNAL(readyRead()),this,SLOT(readPendingDatagrams()) );

    startTimer( 400 );
}

CSimuMW::~CSimuMW()
{
    delete ui;
}

void CSimuMW::closeEvent(QCloseEvent *event)
{
    QSettings settings;
    settings.setValue("geometry",saveGeometry() );
    settings.setValue("windowState",saveState() );
}


void CSimuMW::readPendingDatagrams()
{
    //ui->logR->appendPlainText( QString("bytesAvailable=%1").arg(udp->bytesAvailable()) );
    QByteArray ba;
    QHostAddress sender;
    quint16 senderport;

    while( udp->hasPendingDatagrams() ){
        ba.resize( udp->pendingDatagramSize() );
        udp->readDatagram( (char*)ba.data(),ba.size(),&sender,&senderport );

        QString str;
        QTextStream ts(&str);

        if( ba.size()==sizeof(CPCmd) ){
            ts<<"rcv "<<ba.size()<<" B from "<<sender.toString()<<"@"<<senderport<<"  :   "<< ((CPCmd*)ba.data())->toString();
            pCmd = *((CPCmd*)ba.data());
        }else{
            ts<<"rcv "<<ba.size()<<" B from "<<sender.toString()<<"@"<<senderport;
        }

        ui->logR->appendPlainText( str );

    }

}

void CSimuMW::timerEvent(QTimerEvent *event)
{
    static int i = 0;

    i = ++i%6;

    arrNI[i].pcTime = pCmd.tTime;
    arrNI[i].simuT();
    udp->writeDatagram( (char*)(arrNI+i),sizeof(*arrNI),QHostAddress("255.255.255.255"),50001 );

    ui->log->appendPlainText( arrNI[i].toString()+QString(":%1B").arg(sizeof(*arrNI)) );
}


void CSimuMW::on_btnStart_clicked()
{

}

void CSimuMW::on_btnClearLogs_clicked()
{
    ui->log->clear();
    ui->logR->clear();
}
