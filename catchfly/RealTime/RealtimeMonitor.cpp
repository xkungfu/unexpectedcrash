#include "RealtimeMonitor.h"
#include <vector>

#include "windows.h"

#include "global.h"
#include "globalplus.h"

#include "RealtimeData.h"


RealtimeMonitor::RealtimeMonitor()
{

}

void wait(int msecond) {

    qDebug() << "[MaintoolbarWidget ... wait] msecond: " << msecond;

    QEventLoop loop;
    QTimer timer;
    QObject::connect(&timer,SIGNAL(timeout()), &loop,SLOT(quit()));
    timer.start(msecond);
    loop.exec();
}


void RealtimeMonitor::dongfangcaifu_realtime_handler_1(bool cancle)
{

    qDebug() << "[dongfangcaifu_realtime_handler_1] cancle: " << cancle;

    global.ISREALTIMETASKCANCALED = cancle;

    //set only one thread:
    QThreadPool::globalInstance()->setMaxThreadCount(1);
    auto worker = [=](int value) {

        qDebug() << "[dongfangcaifu_realtime_handler_2] iterating 1 +++++++++++++++++++++++++++++++++++++++++++++++++++++++ ";

        RealtimeData* RD = new RealtimeData();
        DongfancaifuRealtimData realtimedata = RD->dongfangcaifu_realtime_data_handler();

        emit update_boardsnapshot_fromrealmonitor(realtimedata);

        //wait(5000);
        Sleep(5000);

        return value * value;
    };

    QList<int> int_qlist;
    for (int i = 0; i < 20000; i++) {
        int_qlist << i;
    }

    if(global.ISREALTIMETASKCANCALED == true)
    {
        global.ISREALTIMETASKCANCALED = false;
        m_future.cancel();
    } else {
        global.ISREALTIMETASKCANCALED = true;
        m_future = QtConcurrent::map(int_qlist, worker);
    }

}


int RealtimeMonitor::worker() {


    for(int i=0; i< 20000; i++)
    {

        qDebug() << "[dongfangcaifu_realtime_handler_2] iterating 2 +++++++++++++++++++++++++++++++++++++++++++++++++++++++ ";
        if(global.ISREALTIMETASKCANCALED == true)
        {
            break;
        }

        m_mutex.lock();

        RealtimeData* RD = new RealtimeData();
        DongfancaifuRealtimData realtimedata = RD->dongfangcaifu_realtime_data_handler();

        emit update_boardsnapshot_fromrealmonitor(realtimedata);

        m_mutex.unlock();

        //wait(5000);
        Sleep(5000);
    }
    return 0;
};

void RealtimeMonitor::dongfangcaifu_realtime_handler_2(bool cancle)
{

    qDebug() << "[dongfangcaifu_realtime_handler_2] cancle: " << cancle;

    global.ISREALTIMETASKCANCALED = cancle;

    //set only one thread:
    QThreadPool::globalInstance()->setMaxThreadCount(1);

    m_future = QtConcurrent::run(this, &RealtimeMonitor::worker);

}
