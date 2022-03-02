#ifndef CANDLECREATORDF_H
#define CANDLECREATORDF_H
#include "qcustomplot.h"



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

class CandleCreatorDF : public QWidget
{
    Q_OBJECT
public:
    explicit CandleCreatorDF(QWidget *parent = nullptr);
    ~CandleCreatorDF();

    //QCustomPlot* setupCandlestick(std::string tickerstr, std::string limit="160", std::string beginstr="", std::string endstr = get_last_trade_date(), std::string focus_date_str="", std::string scale="");
    QCustomPlot* setupCandlestick(std::map<std::string, std::string> param_map);

    QVector<double> calculateMA(const QVector<QVector<double> > &v, int dayCount);
private:
    static bool findmin(QCPFinancialData const & s1, QCPFinancialData const & s2);
    static bool findmax(QCPFinancialData const & s1, QCPFinancialData const & s2);
    std::ostream& log() const{ return *m_log; }
    mutable std::ostream* m_log;


};
#endif //CANDLECREATORDF_H
