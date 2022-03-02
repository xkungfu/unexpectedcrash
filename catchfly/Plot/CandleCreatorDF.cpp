/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2021 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 29.03.21                                             **
**          Version: 2.1.0                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/
#include "CandleCreatorDF.h"
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <iostream>
#include "qcustomplot.h"

#include "global.h"
#include "globalplus.h"

//文字轴：
class MyAxisTickerText : public QCPAxisTickerText
{
protected:
    virtual QVector<double> createTickVector(double tickStep, const QCPRange &range) Q_DECL_OVERRIDE
    {
        qDebug() << "[CandleCreatorDF>>MyAxisTickerText] tickStep: " << tickStep << " range: " << range;

        Q_UNUSED(tickStep)
        QVector<double> result;
        if (mTicks.isEmpty())
            return result;

        auto start = mTicks.lowerBound(range.lower);
        auto end = mTicks.upperBound(range.upper);

        if (start != mTicks.constBegin()) --start;
        if (end != mTicks.constEnd()) ++end;

        int count = cleanMantissa(std::distance(start, end) / double(mTickCount + 1e-10));
        qDebug() << "[CandleCreatorDF>>MyAxisTickerText] count: " << count;

        auto it = start;
        while (it != end) {
            result.append(it.key());
            int step = count;
            if (step == 0) ++it;
            while (--step >= 0 && it != end)
                ++it;
        }

        qDebug() << "[CandleCreatorDF>>MyAxisTickerText] result: " << result;

        return result;
    }
};


CandleCreatorDF::CandleCreatorDF(QWidget *parent) : QWidget(parent)
{
}

CandleCreatorDF::~CandleCreatorDF()
{
    //qDebug()<<__LINE__<<__FUNCTION__;
}


bool CandleCreatorDF::findmin(QCPFinancialData const & s1, QCPFinancialData const & s2)
{
    return s1.low < s2.low;
}
bool CandleCreatorDF::findmax(QCPFinancialData const & s1, QCPFinancialData const & s2)
{
    return s1.high < s2.high;
}



/* 计算均线 ====================================================================================
*/
QVector<double> CandleCreatorDF::calculateMA(const QVector<QVector<double> > &v, int dayCount)
{
    auto func = [](double result, const QVector<double> &v2){
        return result + v2[1];
    };

    QVector<double> result;
    for (int i = 0; i < v.size(); ++i) {
        if (i < dayCount) {
            result.append(qQNaN());
        } else {
            double sum = std::accumulate(v.begin() + i - dayCount + 1, v.begin() + i + 1, 0.0, func);
            result.append(sum / dayCount);
        }
    }
    return result;
}


QCustomPlot* CandleCreatorDF::setupCandlestick(std::map<std::string, std::string> param_map)
{

    std::string tickerstr = param_map.contains("tickerstr") ? param_map["tickerstr"] : "300670";
    std::cout << "[CandleCreatorDF>>setupCandlestick] ticker_str: " << tickerstr << std::endl;

    QCustomPlot *customPlot = new QCustomPlot();
    //return customPlot;

    //basic info of a security =======================================================================================================================================
    const char* cache_fullpath_char = "../temp/secturity_info.csv";
    std::cout << "[CandleCreatorDF>>setupCandlestick_df] cache_fullpath_char: " << cache_fullpath_char << std::endl;
    ULDataFrame secdf;
    try  {
        secdf.read(cache_fullpath_char, io_format::csv2);
    }
    catch (const DataFrameError &ex)  {
        std::cout << "[CandleCreatorDF>>setupCandlestick_df] dataframe read catch DataFrameError error: " << ex.what() << std::endl;
    }

    std::cout << "[CandleCreatorDF>>setupCandlestick] secdf: "; secdf.write<std::ostream, std::string, double>(std::cout, io_format::csv2);

    std::string sec_full_name = secdf.get_row<std::string>(0, {"sec_full_name"}).at<std::string>(0);
    //std::string sec_full_name = secdf.get_column<std::string>("sec_full_name")[0];


    //daily data of the secturity =======================================================================================================================================
    cache_fullpath_char = "../temp/dailydata.csv";
    std::cout << "[CandleCreatorDF>>setupCandlestick_df] cache_fullpath_char: " << cache_fullpath_char << std::endl;
    ULDataFrame dailydf;
    try  {
        dailydf.read(cache_fullpath_char, io_format::csv2);
    }
    catch (const DataFrameError &ex)  {
        std::cout << "[CandleCreatorDF>>setupCandlestick_df] dataframe read catch DataFrameError error: " << ex.what() << std::endl;
    }


    if(dailydf.empty()){
        std::cout << "[CandleCreatorDF>>setupCandlestick] daily data lost ... " << std::endl;
        return customPlot;
    }

    //添加当日实时数据：
    qDebug() << "[CandleCreatorDF>>setupCandlestick] global.ISINTRADINGTIME: " << global.ISINTRADINGTIME;
    //if(1==1)
    if(global.ISINTRADINGTIME)
    {
        std::cout << "[CandleCreatorDF>>setupCandlestick] patch REALTIMEDFCOPY ... " << std::endl;
        ULDataFrame realtimedf;

        realtimedf = global.REALTIMEDFCOPY;

        if(!realtimedf.empty())
        {

            auto functor = [tickerstr](const unsigned long &, const std::string &val)-> bool { return (val == tickerstr); };
            ULDataFrame ticker_new_df = realtimedf.get_data_by_sel<std::string, decltype(functor), double, std::string>("ticker", functor);
            std::cout << "[CandleCreatorDF>>setupCandlestick] ticker_new_df: "; ticker_new_df.write<std::ostream, std::string, double>(std::cout, io_format::csv2);


            //修改新添加的最后一行的索引值：
            //新添加的行的索引值：
            unsigned long indexnumber = ticker_new_df.get_index()[0];
            ticker_new_df.replace_index({ indexnumber }, { (unsigned long)dailydf.get_index().size() }); //查找到左列值将被替换为对应的右列值
            std::cout << "[CandleCreatorDF>>setupCandlestick] ticker_new_df: "; ticker_new_df.write<std::ostream, std::string, double>(std::cout, io_format::csv2);

            //连接新数据：
            dailydf.self_concat<decltype(ticker_new_df), double, std::string>(ticker_new_df, true);


        }
    }

    //std::cout << "[CandleCreatorDF>>setupCandlestick] dailydf: "; dailydf.write<std::ostream, std::string, double>(std::cout, io_format::csv2);

    int daily_size = dailydf.get_index().size();
    qDebug() << "[CandleCreatorDF>>setupCandlestick] daily_size: " << daily_size;

    QSharedPointer<QCPAxisTickerText> textTickerx(new MyAxisTickerText);     // data of xaxis
    textTickerx->setTickCount(10);

    QCPDataContainer<QCPFinancialData> price_daily_data; //价格数据
    QVector<double> MA5_daily_data, MA10_daily_data, MA20_daily_data, MA30_daily_data, MA60_daily_data; //时间轴 均线数据
    double ma5_i, ma10_i, ma20_i, ma30_i, ma60_i;

    double focusposition_double = 0;
    double maskposition_double = 0;
    double focusposition_low_double = 0;

    //colors of average line：
    const QVector<QColor> ColorOptions = {
        //"#c23531", "#2f4554", "#61a0a8", "#d48265"
        QColor(194, 53, 49), QColor(47, 69, 84), QColor(97, 160, 168), QColor(212, 130, 101),
    };

    std::cout << "[CandleCreatorDF>>setupCandlestick] iteerate dailydf ";
    for (unsigned int i = 0; i < daily_size; i++)
    {
        std::cout << " /i: " << i; //

        const auto row = dailydf.get_data_by_idx<double, std::string>(std::vector<ULDataFrame::IndexType> { i });
        //std::cout << "[CandleCreatorDF>>secdf] row: "; row.write<std::ostream, double, std::string>(std::cout, io_format::csv2);
        //output result:
        //INDEX:1:<ulong>,amplitude:1:<double>,average:1:<double>,change_percentage:1:<double>,close_price:1:<double>,divergence_h_highest:1:<double>,divergence_h_lowest:1:<double>,highest_price:1:<double>,lowest_price:1:<double>,ma10:1:<double>,ma20:1:<double>,ma3:1:<double>,ma30:1:<double>,ma5:1:<double>,ma60:1:<double>,name:1:<string>,nonrest_float_amount:1:<double>,open_price:1:<double>,ticker:1:<string>,trade_date:1:<string>,tradestatus:1:<double>,turnover_amount:1:<double>,turnover_rate:1:<double>,turnover_vol:1:<double>,turnover_vol_ratio:1:<double>
        //245,3.93,9.44,-3.52,9.32,0,0,9.7,9.32,9.59,9.63,9.56,9.92,9.64,10.49,,19.6456,9.7,300670,2022-01-20,1,4.35935e+07,2.18,4.61773e+08,1.18

        //std::string current_trade_date = row.get_column<std::string>("trade_date")[0];

        // data of current day：
        QCPFinancialData day;
        day.key = i;
        day.open = row.get_column<double>("open_price")[0];
        day.close = row.get_column<double>("close_price")[0];
        day.low = row.get_column<double>("lowest_price")[0];
        day.high = row.get_column<double>("highest_price")[0];
        price_daily_data.add(day);

        ma5_i =  row.get_column<double>("ma5")[0];
        ma10_i =  row.get_column<double>("ma10")[0];
        ma20_i =  row.get_column<double>("ma20")[0];
        ma30_i =  row.get_column<double>("ma30")[0];
        ma60_i =  row.get_column<double>("ma60")[0];

        MA5_daily_data.append(ma5_i);
        MA10_daily_data.append(ma10_i);
        MA20_daily_data.append(ma20_i);
        MA30_daily_data.append(ma30_i);
        MA60_daily_data.append(ma60_i);
    }
    std::cout << std::endl;


    qDebug() << "[CandleCreatorDF>>setupCandlestick] paint plot: ------------------------------------------------------------------------------";


    QColor posibrushcolor = QColor(23, 23, 23, 0);

    //K线实体与边框配色
    const QColor BrushPositive(posibrushcolor);//上涨背景
    const QColor PenPositive(255, 47, 47);//上涨边框
    const QColor BrushNegative(0, 255, 255);//下跌背景
    const QColor PenNegative(0, 255, 255);//深绿下跌边框
    QCPFinancial *financial = new QCPFinancial(customPlot->xAxis, customPlot->yAxis);
    financial->setName("日K");
    financial->setBrushPositive(BrushPositive);
    financial->setPenPositive(PenPositive);
    financial->setBrushNegative(BrushNegative);
    financial->setPenNegative(PenNegative);

    //填充数据：
    financial->data()->set(price_daily_data);

    //设置X轴：
    customPlot->xAxis->setTicker(textTickerx); //X轴数据
    customPlot->rescaleAxes();

    //设置宽度适应缩放：
    //void QCPAxis::scaleRange ( double  factor)  按当前轴范围中心的因子缩放此轴的范围。 K线区域自适应长度的缩放倍数 = 当前界面所有股票K线区域最大长度 / 当前股票K线区域长度
    //取当前界面所有股票K线区域最大长度，作为X轴的scalerange: 由于最大长度需要等所有candle加载完成后才获取，所以取limit设置scaleRange值。
    customPlot->xAxis->scaleRange(1 + 0.05, customPlot->xAxis->range().lower);
    customPlot->yAxis->scaleRange(1, customPlot->yAxis->range().center());

    customPlot->plotLayout()->insertRow(0);
    QCPTextElement *titleElement = new QCPTextElement(customPlot, "test title");
    titleElement->setTextColor(QColor(255, 255, 255));
    titleElement->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
    titleElement->setMargins(QMargins(15, 5, 0, 0)); //设置边距 QMargins::QMargins(int left, int top, int right, int bottom)
    titleElement->setTextFlags(Qt::AlignLeft); //设置对齐
    customPlot->plotLayout()->addElement(0, 0, titleElement);


    //customPlot->legend->setVisible(true);//图例
    //customPlot->setBackground(Qt::lightGray);
    customPlot->setBackground(QColor(23, 23, 23));//K线图整体窗口背景色

    customPlot->xAxis->setLabelColor(QColor(255, 25, 2)); //暂不明
    customPlot->yAxis->setLabelColor(QColor(25, 55, 2)); //暂不明
    customPlot->xAxis->setTickPen(QColor(55, 2, 255)); //暂不明

    customPlot->xAxis->setTickLabelColor(QColor(255, 255, 255)); //轴文字颜色
    customPlot->xAxis->grid()->setZeroLinePen(QPen(QColor(255, 255, 255))); //0轴线颜色
    customPlot->xAxis->grid()->setPen(QPen(QColor(76, 76, 76))); //轴线颜色

    customPlot->yAxis->setTickLabelColor(QColor(255, 255, 255)); //轴文字颜色
    customPlot->yAxis->grid()->setZeroLinePen(QPen(QColor(255, 255, 255))); //0轴线颜色
    customPlot->yAxis->grid()->setPen(QPen(QColor(76, 76, 76))); //轴线颜色

    //设置Y轴坐标范围:
    //查找所有数据中 low 的最小值
    QCPFinancialData fdata_min = *std::min_element(financial->data()->begin(), financial->data()->end(), findmin);
    //qDebug () << "[CandleCreatorDF>>setupCandlestick] fdata_min: " << fdata_min.low; // fdata_min:  7.68
    QCPFinancialData fdata_max = *std::max_element(financial->data()->begin(), financial->data()->end(), findmax);
    //qDebug () << "[CandleCreatorDF>>setupCandlestick] fdata_max: " << fdata_max.high; // fdata_max:  14.5
    customPlot->yAxis->setRange(fdata_min.low-1, fdata_max.high+1);


    customPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //customPlot->installEventFilter(this);

    return customPlot;

}
