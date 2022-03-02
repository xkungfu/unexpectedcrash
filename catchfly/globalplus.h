#pragma once
#include "global.h"
#include <iostream>
#include <QtConcurrent/QtConcurrent>

inline void generate_boardinfo();
inline void generate_boardcontainsinfo();
inline QMutex mMutex;
inline QReadWriteLock mrwlock;
struct GlobalPlus
{
    void ChangeGlobal() {
        global.i++;
        global.ISINTRADINGTIME = true;
    }


    void setGlobal_boardinfo(){
        generate_boardcontainsinfo();
    }

    void setGlobal_realtimedf(ULDataFrame sec_realtime_df)
    {
        qDebug() << "[globalplus.h>>setGlobal_realtimedf] write ... ";
        global.REALTIMEDF = sec_realtime_df;
        return;
    }

    ULDataFrame getGlobal_realtimedf()
    {
        qDebug() << "[globalplus.h>>getGlobal_realtimedf] read ... ";
        return global.REALTIMEDF;
    }


};



//生成每个板块成份股列表文件：
inline void generate_boardcontainsinfo()
{
    std::cout << "[[globalplus.h>>generate_boardcontainsinfo] ... " << std::endl;
    //循环板块：
    QMap<QString, QMap<QString, QString>> cyb_boardcontainsinfo_qmap, normal_boardcontainsinfo_qmap;

    //读入缓存：
    QString cyb_boardcontainsinfo_qmap_cache_file = "../temp/cyb_boards_contains_qmap.txt";
    QString normal_boardcontainsinfo_qmap_cache_file = "../temp/normal_boards_contains_qmap.txt";
    QFile* f1 = new QFile(cyb_boardcontainsinfo_qmap_cache_file);
    f1->open(QIODevice::ReadOnly); //以只读方式打开txt
    QDataStream in1(f1); //创建QDataStream对象并与QFile对象关联
    in1 >> cyb_boardcontainsinfo_qmap; //把文件读入 cyb_board_df_qlist_sorted
    f1->close(); //关闭文件

    QFile* f2 = new QFile(normal_boardcontainsinfo_qmap_cache_file);
    f2->open(QIODevice::ReadOnly); //以只读方式打开txt
    QDataStream in2(f2); //创建QDataStream对象并与QFile对象关联
    in2 >> normal_boardcontainsinfo_qmap; //把文件读入 cyb_board_df_qlist_sorted
    f2->close(); //关闭文件

    //qDebug() << "[generate_boardcontainsinfo] cyb_boardcontainsinfo_qmap: " << cyb_boardcontainsinfo_qmap << " normal_boardcontainsinfo_qmap: "<< normal_boardcontainsinfo_qmap;
    global.BOARDCONTAINSINFO_CYB_QMAP = cyb_boardcontainsinfo_qmap;
    global.BOARDCONTAINSINFO_NORMAL_QMAP = normal_boardcontainsinfo_qmap;
}



inline QString file_read_q(QString fullpath){
    QFile f(fullpath);
    if(f.open(QIODevice::ReadOnly | QIODevice::Text)){
        return f.readAll();
    }
    return "";
}
