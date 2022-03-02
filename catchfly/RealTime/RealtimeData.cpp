#include "RealtimeData.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <QtConcurrent/QtConcurrent>

RealtimeData::RealtimeData()
{

}

DongfancaifuRealtimData RealtimeData::dongfangcaifu_realtime_data_handler(){

    qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] start generate realtime data ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ";

    m_mutex.lock();

    DongfancaifuRealtimData tempdcdata = {};

    //read realtime data from file:
    ULDataFrame sec_realtime_df;
    try  {
        std::string cache_path = "../temp/realtime-2022-02-21-23-01-37.csv";
        std::ifstream f(cache_path.c_str());
        std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] file exists: " << std::boolalpha << f.good() << std::endl; //

        sec_realtime_df.read(cache_path.c_str(), io_format::csv2);

        GlobalPlus GP;
        GP.setGlobal_realtimedf(sec_realtime_df);

    }
    catch (const DataFrameError &ex)  {
        std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] [WARNING] REDIS GET ERROR! e.what(): " << ex.what() << std::endl;
        return tempdcdata;
    }

    //std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] sec_realtime_df: "; sec_realtime_df.write<std::ostream, std::string, double>(std::cout, io_format::csv2);

    qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] store sorted data to boardcontainer_qpairlist, and store dataframe data to dfcontainer_qmap ...";

    //data source files:
    QString xx = "../temp/selected_boards_a.txt";
    QString yy = "../temp/selected_boards_b.txt";
    QString content_industry = file_read_q(xx); //
    QString content_concept = file_read_q(yy);

    //QString content_industry = file_read_q(settings->value("BOARDREALTIMESNAPSHOT_INDUSTRYSELECTED").toString());
    //qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] content_industry: " << content_industry;
    QStringList m_filtered_board_qlist_industry = content_industry.split("\n");
    //qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] filtered_board_qlist_industry: " << m_filtered_board_qlist_industry;

    //QString content_concept = file_read_q(settings->value("BOARDREALTIMESNAPSHOT_CONCEPTSELECTED").toString());
    //qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] content_concept: " << content_concept;
    QStringList m_filtered_board_qlist_concept = content_concept.split("\n");
    //qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] filtered_board_qlist_concept: " << m_filtered_board_qlist_concept;

    QStringList all_filtered_board_qlist = m_filtered_board_qlist_industry + m_filtered_board_qlist_concept;
    //移除空值：
    all_filtered_board_qlist.removeAll(QString("")); // Returns the number of entries removed
    //qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] all_filtered_board_qlist: " << all_filtered_board_qlist;


    qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] split dataframe by boards ... ... ";

    //select and concat dataframe：
    QMap<QString, ULDataFrame> dfcontainer_qmap;
    //QMap<QString, double> boardcontainer_qmap;
    QList<QPair<QString, double>> boardcontainer_qpairlist;
    //std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] iterate filtered board board_code: ";
    for(int i=0; i<all_filtered_board_qlist.size(); i++)
    {
        QString current_board_code_qstr = all_filtered_board_qlist[i];
        std::string current_board_code_str = current_board_code_qstr.toStdString();
        //std::cout << " / " << current_board_code_str;

        QMap<QString, QString> current_board_contains = global.BOARDCONTAINSINFO_CYB_QMAP[current_board_code_qstr];
        //qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] current_board_contains: " << current_board_contains;

        if(current_board_contains.empty())
        {
            continue;
        }

        ULDataFrame resultdf;
        for(auto el : current_board_contains.keys())
        {
            std::string ticker_str = el.toStdString();
            //std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] all_filtered_board_qlist current_board_contains ticker_str: " << ticker_str << std::endl;

            //select:
            auto functor1 = [ticker_str](const unsigned long &, const std::string &val)-> bool { return (val == ticker_str); };
            ULDataFrame tempdf = sec_realtime_df.get_data_by_sel<std::string, decltype(functor1), double, std::string>("ticker", functor1);
            //std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] tempdf: "; tempdf.write<std::ostream, std::string, double>(std::cout, io_format::csv2);

            //concat:
            resultdf = resultdf.concat<decltype(tempdf), double, std::string>(tempdf);
        }

        QList<QString> contains_qvec = current_board_contains.keys();

        //select and concat dataframe another way：
        //auto functor1 = [contains_qvec](const unsigned long &, const std::string &val)-> bool { return contains_qvec.contains(QString::fromStdString(val)); };
        //resultdf = sec_realtime_df.get_data_by_sel<std::string, decltype(functor1), double, std::string>("ticker", functor1);


        //std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] resultdf: "; resultdf.write<std::ostream, std::string, double>(std::cout, io_format::csv2);


        //sort and reindex：
        resultdf.sort<double, double, std::string>("change_percentage", sort_spec::desce);

        std::vector<unsigned long> ulvec(resultdf.get_index().size());
        unsigned long index = 0;
        std::generate(ulvec.begin(), ulvec.end(), [&]{ return index++; });
        resultdf.load_column("long_col", std::move(ulvec), nan_policy::dont_pad_with_nans);
        resultdf = resultdf.get_reindexed<unsigned long, double, std::string>("long_col", "OLD_IDX");

        //std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] resultdf: ";//resultdf.write<std::ostream, std::string, double>(std::cout, io_format::csv2);

        //store dataframe to qmap variable:
        dfcontainer_qmap[current_board_code_qstr] = resultdf;

        //store one column first value to qlist:
        double highest_change = resultdf.get_column<double>("change_percentage")[0];
        QPair<QString, double> temp_pair(current_board_code_qstr, highest_change);
        boardcontainer_qpairlist.append(temp_pair);

    } // loop all_filtered_board_qlist

    //sort qlist：
    std::sort(boardcontainer_qpairlist.begin(), boardcontainer_qpairlist.end(), [](QPair<QString, double> l, QPair<QString, double> r)
    {
        return l.second > r.second;
    });

    qDebug()<< "[RealtimeData>>dongfangcaifu_realtime_data_handler] store data to struct DongfancaifuRealtimData ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ... ";

    DongfancaifuRealtimData dcdata;
    dcdata.qpairlistdata = boardcontainer_qpairlist;
    dcdata.qmapdata = dfcontainer_qmap;
    dcdata.empty = false;

    m_mutex.unlock();

    return dcdata;

}
