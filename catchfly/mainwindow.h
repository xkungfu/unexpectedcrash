#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RealTime/boardsnapshot.h"
#include "RealTime/RealtimeMonitor.h"
#include "global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
    signals:
        void update_boardsnapshot_frommainwindow(DongfancaifuRealtimData realtimedata);
    private slots:
        void on_actionstart_1_triggered();
        void on_actionstop_1_triggered();

        void on_actionstart_2_triggered();
        void on_actionstop_2_triggered();

    private:
        Ui::MainWindow *ui;
        BoardSnapshot *m_boardsnapshotwdt;
        RealtimeMonitor* realmonitor;

};
#endif // MAINWINDOW_H
