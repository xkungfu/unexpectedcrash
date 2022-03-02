#include "CandleBoardContains.h"
#include "ui_CandleBoardContains.h"
#include <QDebug>
#include <QList>
#include "global.h"
#include "qcustomplot.h"
#include "Plot/CandleCreatorDF.h"


CandleBoardContains::CandleBoardContains(QWidget *parent, QMap<QString, QString> param_qmap) :
    //QWidgetsListWidget(parent),
    ui(new Ui::CandleBoardContains)
{
    ui->setupUi(this);

    if(!param_qmap.empty())
    {
        switch_candlelist(param_qmap);
    }

}

CandleBoardContains::~CandleBoardContains()
{
    qDebug()<< "[CandleBoardContains>>~CandleBoardContains] delete: " <<__LINE__<<__FUNCTION__;
    delete ui;
}

void CandleBoardContains::switch_candlelist(QMap<QString, QString> param_qmap)
{

    //parse parameter：
    QString board_code_qstr = param_qmap["boardcodeqstr"];

    //contains of a board：
    QMap<QString, QString> boardcontains_qmap = global.BOARDCONTAINSINFO_CYB_QMAP[board_code_qstr];
    qDebug()<< "[CandleBoardContains>>switch_candlelist] boardcontains_qmap: " << boardcontains_qmap; //QMap(("300084", "海默科技")("300157", "恒泰艾普")("300164", "通源石油")("300191", "潜能恒信"))
    QStringList boardcontains_list = boardcontains_qmap.keys();
    qDebug()<< "[CandleBoardContains>>switch_candlelist] boardcontains_list: " << boardcontains_list; // ("300084", "300157", "300164", "300191")

    QVBoxLayout* onevlay = new QVBoxLayout();
    onevlay->setSpacing(22);

    for (int i=0; i<boardcontains_list.size(); i++) {

        Sleep(300);

        std::string ticker_str = boardcontains_list[i].toStdString();

        //create candle stick plot：
        QHBoxLayout *candleplotlay = new QHBoxLayout();
        std::map<std::string, std::string> param_map =
        {
            {"tickerstr", ticker_str},
        };

        //QWidget*  candleplot = new QWidget();

        CandleCreatorDF*  customcandle = new CandleCreatorDF();
        auto candleplot = customcandle->setupCandlestick(param_map);

        candleplot->setObjectName("name");
        candleplot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        candleplot->setMaximumHeight(m_height);
        candleplot->setLayout(candleplotlay);

        onevlay->addWidget(candleplot);

    }

    ui->onewdt->setLayout(onevlay);

    return;
} //switch_candlelist


