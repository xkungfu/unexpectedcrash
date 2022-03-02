#ifndef RealtimeMonitor_H
#define RealtimeMonitor_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include <QFuture>
#include "global.h"

class RealtimeMonitor : public QObject
{
    Q_OBJECT
    public:
        RealtimeMonitor();
        void dongfangcaifu_realtime_handler_1(bool cancle);
        void dongfangcaifu_realtime_handler_2(bool cancle);

    signals:
        void update_boardsnapshot_fromrealmonitor(DongfancaifuRealtimData realtimedata);

    private:
        int worker();
        //QFuture<int> m_future;
        QFuture<void> m_future;

        QMutex m_mutex;

};

#endif // RealtimeMonitor_H
