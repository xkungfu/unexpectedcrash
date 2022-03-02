#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //====tab==== 板块监控  =========================================================================================================================================
    QWidget* tab_boardsnapshot_body = new QWidget();
    //tabwidget->addTab(tab_boardsnapshot_body,"板块涨停趋势");


    QMap<QString, QString> boardsnapshot_qmap;

    BoardSnapshot *m_boardsnapshotwdt = new BoardSnapshot(tab_boardsnapshot_body);
    m_boardsnapshotwdt->setMinimumSize(333, 444);

    m_boardsnapshotwdt->setSizePolicy(QSizePolicy:: Expanding, QSizePolicy:: Expanding);

    QVBoxLayout *boardsnapshot_layout = new QVBoxLayout();
    boardsnapshot_layout->addWidget(m_boardsnapshotwdt);
    tab_boardsnapshot_body->setLayout(boardsnapshot_layout);

    setCentralWidget(m_boardsnapshotwdt);


    connect(this, SIGNAL(update_boardsnapshot_frommainwindow(DongfancaifuRealtimData)), m_boardsnapshotwdt, SLOT(dynamic_update_snapshot(DongfancaifuRealtimData)));
    //connect(m_boardsnapshotwdt, SIGNAL(boardsnapshot_close_realtimedata_future()), toolbar_wdt, SLOT(at_boardsnapshot_close_realtimedata_future()));



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionstart_1_triggered()
{
    realmonitor = new RealtimeMonitor();
    realmonitor->dongfangcaifu_realtime_handler_1(false);
    connect(realmonitor, SIGNAL(update_boardsnapshot_fromrealmonitor(DongfancaifuRealtimData)), this, SIGNAL(update_boardsnapshot_frommainwindow(DongfancaifuRealtimData)));
}


void MainWindow::on_actionstop_1_triggered()
{
    realmonitor->dongfangcaifu_realtime_handler_1(true);
}


void MainWindow::on_actionstart_2_triggered()
{
    realmonitor = new RealtimeMonitor();
    realmonitor->dongfangcaifu_realtime_handler_2(false);
    connect(realmonitor, SIGNAL(update_boardsnapshot_fromrealmonitor(DongfancaifuRealtimData)), this, SIGNAL(update_boardsnapshot_frommainwindow(DongfancaifuRealtimData)));
}


void MainWindow::on_actionstop_2_triggered()
{
    realmonitor->dongfangcaifu_realtime_handler_2(true);
}

