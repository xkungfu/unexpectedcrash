#include "mainwindow.h"
#include <QApplication>

#include "global.h"
#include "globalplus.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("TEST");
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);

    // ======== global 初始化 ===============================================================================================================
    GlobalPlus gp;
    gp.ChangeGlobal();//常用的一些变量在此函数设置
    gp.setGlobal_boardinfo();

    qRegisterMetaType<DongfancaifuRealtimData>();

    MainWindow w;
    w.show();
    return a.exec();
}
