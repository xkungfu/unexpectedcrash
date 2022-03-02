#ifndef REALTIMEDATA_H
#define REALTIMEDATA_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include "global.h"
#include "globalplus.h"

#include <QMutexLocker>

class RealtimeData
{
    public:
        RealtimeData();
        void get_sec_realtime();
        DongfancaifuRealtimData dongfangcaifu_realtime_data_handler();

    private:
        double m_check1 = 666;
        double m_check2 = 666;
        double m_check3 = 666;
        QMutex m_mutex;



};

#endif // REALTIMEDATA_H
