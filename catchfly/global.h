#ifndef GLOBAL_H
#define GLOBAL_H
#include <QMetaType>
#include <QMap>
#include <iostream>


#include <DataFrame/DataFrame.h>  // Main DataFrame header
#include <DataFrame/DataFrameFinancialVisitors.h>  // Financial algorithms
#include <DataFrame/DataFrameMLVisitors.h>  // Machine-learning algorithms
#include <DataFrame/DataFrameStatsVisitors.h>  // Statistical algorithms
// DataFrame library is entirely under hmdf name-space
using namespace hmdf;
// A DataFrame with ulong index type
using ULDataFrame = StdDataFrame<unsigned long>;
// A DataFrame with string index type
using StrDataFrame = StdDataFrame<std::string>;


struct  DongfancaifuRealtimData  {
    DongfancaifuRealtimData(){};
    ~DongfancaifuRealtimData(){};
    QList<QPair<QString, double>> qpairlistdata;//板块实时排行
    QMap<QString, ULDataFrame> qmapdata;//板块实时数据
    bool empty = true;
};
Q_DECLARE_METATYPE(DongfancaifuRealtimData);

class Global
{
public:
    int i = 100;


    QMap<QString, QString> BOARDINFO_QMAP = {};


    QMap<QString, QMap<QString, QString>> BOARDCONTAINSINFO_CYB_QMAP = {};
    QMap<QString, QMap<QString, QString>> BOARDCONTAINSINFO_NORMAL_QMAP = {};

    QMap<QString, QMap<QString, QString>> BOARDCONTAINSINFO_CYB_QMAPCOPY = {};
    QMap<QString, QMap<QString, QString>> BOARDCONTAINSINFO_NORMAL_QMAPCOPY = {};

    bool ISREALTIMETASKEXISTS = false;
    bool ISREALTIMETASKCANCALED = false;
    ULDataFrame REALTIMEDF = {};
    ULDataFrame REALTIMEDFCOPY = {};
    int REALTIMEINTERVAL = 3;
    bool bugcheck = false;

    bool ISINTRADINGTIME = false;
    DongfancaifuRealtimData DONGFANGCAIFUREALTIMEDATA = {};

    std::string realtime_check = "";

public:
    Global() = default;
    Global(const Global&) = delete;
    Global(Global&&) = delete;

    static Global& Instance()
    {
        static Global global;
        return global;
    }
};

namespace {
    Global& global = Global::Instance();
}
// static Global& global = Global::Instance(); if you like

#endif //GLOBAL_H
