#include "boardsnapshot.h"
#include "ui_BoardSnapshot.h" // Non-portable path to file '"ui_boardsnapshot.h"'; specified path differs in case from file name on disk (fix available)

#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <iostream>
#include <qcustomplot.h>

#include "globalplus.h"


#include <QtConcurrent/QtConcurrentRun>

#include "Board/containsshow/CandleBoardContains.h"


//动态创建按钮： https://stackoverflow.com/questions/47625754/executing-dynamically-created-buttons
BoardSnapshot::BoardSnapshot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoardSnapshot)
{
    ui->setupUi(this);

    //dynamic_update_snapshot();

}

BoardSnapshot::~BoardSnapshot()
{
    qDebug()<<__LINE__<<__FUNCTION__;
    //delete mLabel;
    delete ui;
}
/*
{"ticker", "string"},
{"name", "string"},
{"trade_date", "string"},
{"open_price", "double"},
{"highest_price", "double"},
{"lowest_price", "double"},
{"close_price", "double"},
{"turnover_vol", "double"},
{"turnover_amount", "double"},
{"amplitude", "double"},
{"change_percentage", "double"},
{"turnover_rate", "double"},
{"average", "double"},
{"turnover_vol_ratio", "double"},
{"ma3", "double"},
{"ma5", "double"},
{"ma10", "double"},
{"ma20", "double"},
{"ma30", "double"},
{"ma60", "double"},
{"tradestatus", "double"},
{"divergence_h_highest", "double"},
{"divergence_h_lowest", "double"},
{"nonrest_float_amount", "double"}
*/

void BoardSnapshot::dynamic_update_snapshot(DongfancaifuRealtimData realtimedata)
{

    qDebug()<< "[BoardSnapshot>>dynamic_update_snapshot] realtimedata: " << realtimedata.empty;

    m_mutex.lock();

    if(realtimedata.empty){
        return;
    }

    QList<QPair<QString, double>> boardcontainer_qpairlist = realtimedata.qpairlistdata;
    QMap<QString, ULDataFrame> dfcontainer_qmap = realtimedata.qmapdata;

    qDebug()<< "[BoardSnapshot>>dynamic_update_snapshot] boardcontainer_qpairlist size: " << boardcontainer_qpairlist.size();

    if(boardcontainer_qpairlist.empty()){
        return;
    }


    //qDebug()<< "[BoardSnapshot>>dynamic_update_snapshot] boardcontainer_qpairlist 2: " << boardcontainer_qpairlist;

    if(!scrollarea){
        qDebug()<< "[BoardSnapshot>>dynamic_update_snapshot>>plot] onewdt has no layout 1 ... ";
        onewdtlay = new QVBoxLayout();
        ui->onewdt->setLayout(onewdtlay);
        ui->onewdt->setMinimumSize(999, 999);
        ui->onewdt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        m_anotherwdt = new QWidget();
        m_anotherwdt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_anotherwdt->setMaximumWidth(2450);

        scrollarea = new QScrollArea();
        scrollarea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        onewdtlay->addWidget(scrollarea); // <-- put scroll area into the layout

        scrollarea->setWidget(m_anotherwdt);
        scrollarea->setWidgetResizable(true); // <-- allow the scroll area to manage its client widget size


    } else {

        qDebug()<< "[BoardSnapshot>>dynamic_update_snapshot>>plot] m_anotherwdt: " << scrollarea;
        delete scrollarea;

        m_anotherwdt = new QWidget();
        m_anotherwdt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        m_anotherwdt->setMaximumWidth(2450);

        scrollarea = new QScrollArea();
        scrollarea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        onewdtlay->addWidget(scrollarea); // <-- put scroll area into the layout

        scrollarea->setWidget(m_anotherwdt);
        scrollarea->setWidgetResizable(true); // <-- allow the scroll area to manage its client widget size

    }


    QVBoxLayout* templay = new QVBoxLayout();
    templay->setSpacing(22);
    m_anotherwdt->setLayout(templay);
    m_anotherwdt->setStyleSheet("background-color: lightgray;");

    //循环板块，根据此板块的dataframe生成bar图表：
    std::cout << "[BoardSnapshot>>dynamic_update_snapshot>>plot] iterate filtered board: ";
    for (int i=0; i<boardcontainer_qpairlist.size(); i++) {

        QString board_code_qstr = boardcontainer_qpairlist[i].first;
        //qDebug()<< "[BoardSnapshot>>dynamic_update_snapshot>>plot] Ploting boardcontainer_qpairlist ;
        std::string board_name_str = global.BOARDINFO_QMAP[board_code_qstr].toStdString();
        QString board_name_qstr = QString::fromStdString(board_name_str);
        //qDebug()<< "[BoardSnapshot>>dynamic_update_snapshot>>plot] Ploting boardcontainer_qpairlist board_code_qstr: " << board_code_qstr << " board_name_qstr: " << board_name_qstr;

        std::cout << " : " << board_code_qstr.toStdString();

        //用于检测某个板块生成情况，检测后注释：
        //if(board_code_qstr != "BK1040") continue;

        //获取此板块df:
        ULDataFrame current_board_df = dfcontainer_qmap[board_code_qstr];
        //std::cout << "[BoardSnapshot>>dynamic_update_snapshot>>plot] current_board_df: ";current_board_df.write<std::ostream, std::string, double>(std::cout, io_format::csv2);

        //按涨幅分割df,正涨幅，负涨幅分割为二个df:
        auto functor_positive = [](const unsigned long &, const double &val)-> bool { return (val >= 0); };
        ULDataFrame positive_df = current_board_df.get_data_by_sel<double, decltype(functor_positive), double, std::string>("change_percentage", functor_positive);
        //std::cout << "[BoardSnapshot>>dynamic_update_snapshot>>plot] positive_df: ";positive_df.write<std::ostream, std::string, double>(std::cout, io_format::csv2);

        auto functor_negative = [](const unsigned long &, const double &val)-> bool { return (val < 0); };
        ULDataFrame negative_df = current_board_df.get_data_by_sel<double, decltype(functor_negative), double, std::string>("change_percentage", functor_negative);
        //std::cout << "[BoardSnapshot>>dynamic_update_snapshot>>plot] negative_df: ";negative_df.write<std::ostream, std::string, double>(std::cout, io_format::csv2);



        // generate xaxis data：
        QVector<double> ticks_positive, ticks_negative;
        std::vector<unsigned long> indexvec_positive = positive_df.get_index();
        ticks_positive = QVector<double>(indexvec_positive.begin(), indexvec_positive.end());
        std::vector<unsigned long> indexvec_negative = negative_df.get_index();
        ticks_negative = QVector<double>(indexvec_negative.begin(), indexvec_negative.end());

        QVector<QString> tickers_qvec;
        std::vector<std::string> tickers = current_board_df.get_column<std::string>("ticker");
        std::transform(tickers.begin(), tickers.end(), std::back_inserter(tickers_qvec), [](const std::string &v){ return QString::fromStdString(v); });

        QVector<double> ticks;
        QVector<QString> labels;
        //方法1：利用index生成X轴坐标, 需在此之前重设dataframe的index:
        std::vector<unsigned long> indexvec = current_board_df.get_index();

        ticks = QVector<double>(indexvec.begin(), indexvec.end());

        std::vector<std::string> names = current_board_df.get_column<std::string>("name");
        std::transform(names.begin(), names.end(), std::back_inserter(labels), [](const std::string &v){ return QString::fromStdString(v); });


        QCustomPlot* plot = new QCustomPlot();
        //是否启用QCustomPlot的OpenGL硬件加速渲染：
        //customplot->setOpenGl(openGl);
        plot->setBackground(QColor(70, 70, 70));
        //X轴：
        plot->xAxis->setRange(0, ticks.size()+1); //X轴范围
        plot->xAxis->setPadding(0); // X轴和下最外边框之间填充距离
        plot->xAxis->setVisible(false);
        plot->xAxis->setTicks(false); //不显示文字
        plot->xAxis->setSubTicks(false);//不显示副文字
        //背景网格：竖向
        plot->xAxis->grid()->setVisible(false);
        plot->xAxis->grid()->setSubGridVisible(false);

        //Y轴：
        plot->yAxis->setRange(-25, 25);
        plot->yAxis->setPadding(-10);
        plot->yAxis->setVisible(true);
        //Y轴说明文字:
        plot->yAxis->setTicks(false); //不显示文字
        plot->yAxis->setSubTicks(false);//不显示副文字
        //plot->yAxis->setSubTickPen(QPen(Qt::white));
        //背景网格：横向
        plot->yAxis->grid()->setVisible(true);
        plot->yAxis->grid()->setSubGridVisible(false);
        //plot->yAxis->setTickLabelColor(Qt::white);
        //plot->yAxis->setLabelColor(Qt::white);
        plot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        plot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 200, Qt::DotLine));

        //柱状图间距：？？？

        // 声明bar数据：
        QVector<double> bar_positiveData, bar_negativeData;
        double max_change_positive = 0;
        double max_change_negative = 0;

        //positive
        if(ticks_positive.size() > 0){
            std::vector<double> change_positive = positive_df.get_column<double>("change_percentage");
            max_change_positive = change_positive[0];
            bar_positiveData = QVector<double>(change_positive.begin(), change_positive.end());

            // 上涨bar:
            QCPBars *bar_positive = new QCPBars(plot->xAxis, plot->yAxis);
            bar_positive->setAntialiased(false);//抗锯齿
            //bar_positive->setStackingGap(1); //叠放柱状图时设置间隙
            //命名：图表上只需显示一个名称：
            bar_positive->setName(board_code_qstr);
            //上涨颜色：
            bar_positive->setPen(QPen(Qt::red));
            bar_positive->setBrush(Qt::red);
            //柱状图宽度：
            bar_positive->setWidthType(QCPBars::wtAbsolute);
            bar_positive->setWidth(25);
            bar_positive->setData(ticks_positive, bar_positiveData);
        }

        //negative
        if(ticks_negative.size() > 0){

            //下跌数据：
            std::vector<double> change_negative = negative_df.get_column<double>("change_percentage");
            bar_negativeData = QVector<double>(change_negative.begin(), change_negative.end());
            max_change_negative = change_negative[0];

            // 下跌bar:
            QCPBars *bar_negative = new QCPBars(plot->xAxis, plot->yAxis);
            bar_negative->setAntialiased(false);
            //bar_negative->setStackingGap(1);
            //下跌颜色：
            bar_negative->setPen(QPen(Qt::green));
            bar_negative->setBrush(Qt::green);
            bar_negative->setWidthType(QCPBars::wtAbsolute);
            bar_negative->setWidth(25);
            //bar_negative->setName("bar_negative 核能");
            bar_negative->setData(ticks_negative, bar_negativeData);
        }


        double spacing = 0.25;
        for(int x=0; x < ticks.size(); x++){
            double y = 10;
            //if(x >= labels.size() )
            if(x >= 5 )
            {
                break;
            }
            QString barname = labels[x];
            //qDebug()<< "[BoardSnapshot>>dynamic_update_snapshot>>plot] bar text barname: " << barname;

            //Creating and configuring an item
            QCPItemText *textLabel = new QCPItemText(plot);
            textLabel->setClipToAxisRect(false);
            textLabel->position->setAxes(plot->xAxis,plot->yAxis);
            textLabel->position->setType(QCPItemPosition::ptPlotCoords);
            //placing the item over the bar with a spacing of 0.25
            textLabel->position->setCoords(x+1.2,y+spacing);
            //Customizing the item
            textLabel->setText(barname);
            textLabel->setRotation(-60);

            textLabel->setFont(QFont(font().family(), 11));
            textLabel->setColor(Qt::white);
            //textLabel->setPen(QPen(Qt::white));
        }

        //总图表上的板块名称:
        //定义最大涨幅：
        double max_change = max_change_positive > 0 ? max_change_positive : max_change_negative;

        QCPItemText *textlabel_main = new QCPItemText(plot);
        textlabel_main->setPositionAlignment(Qt::AlignTop|Qt::AlignRight);
        textlabel_main->position->setType(QCPItemPosition::ptAxisRectRatio);
        textlabel_main->position->setCoords(1.0, 0); // place position at center/top of axis rect
        textlabel_main->setText("CLICK PLOT TO OPEN NEW WINDOW");
        textlabel_main->setFont(QFont(font().family(), 14)); // make font a bit larger
        textlabel_main->setColor(QColor(250, 200, 20)); //文字颜色
        //textlabel_main->setPen(QPen(Qt::white)); //文字边框颜色


        //关闭互动
        //plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

        double min_width = ticks.size() > 8 ? ticks.size() * 20 : 160;
        plot->setMinimumWidth(min_width);
        plot->setMinimumHeight(90);
        //事件透明：
        //plot->setAttribute(Qt::WA_TransparentForMouseEvents);
        //边距：
        plot->setContentsMargins(0, 0, 0, 0); //对plot内图表边距不起作用
        plot->axisRect()->setAutoMargins(QCP::msNone); //与setMargins配合使用
        plot->axisRect()->setMargins(QMargins(2, 2, 2, 2)); //坐标轴到外部窗口之间的间距

        plot->setObjectName(board_code_qstr);
        plot->installEventFilter(this);
        plot->setMouseTracking(true);

        //plot->replot();

        templay->addWidget(plot);

    }

    m_mutex.unlock();

    return;

} //--dynamic_update_snapshot



bool BoardSnapshot::eventFilter(QObject *obj, QEvent *qevt)
{

    if (qevt->type() == QEvent::MouseButtonDblClick) { //MouseButtonDblClick

        //关闭异步实时数据线程:
        //emit boardsnapshot_close_realtimedata_future();

        QCustomPlot *plot =  qobject_cast<QCustomPlot*>(qobject_cast<QObject*>(obj));
        QString board_code_qstr = plot->objectName();
        qDebug() << "[BoardSnapshot>>eventFilter] MouseButtonDblClick board_code_qstr: " << board_code_qstr; //


        //从文件读取dataframe:
        ULDataFrame sec_realtime_df;
        try  {
            std::string cache_path = "../temp/realtime-2022-02-21-23-01-37.csv";
            std::ifstream f(cache_path.c_str());
            std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] file exists: " << std::boolalpha << f.good() << std::endl; //

            sec_realtime_df.read(cache_path.c_str(), io_format::csv2);

            global.REALTIMEDFCOPY = sec_realtime_df;

        }
        catch (const DataFrameError &ex)  {
            std::cout << "[RealtimeData>>dongfangcaifu_realtime_data_handler] [WARNING] REDIS GET ERROR! e.what(): " << ex.what() << std::endl;
            return false;
        }

        qDebug() << "[BoardSnapshot>>eventFilter] MouseButtonDblClick board_code_qstr: " << board_code_qstr; //"BK0730"
        qDebug() << "[BoardSnapshot>>eventFilter] MouseButtonDblClick mPopup: " << mPopup; //QWidget(0x0) 或 QWidget(0x24e3eeb44f0)

        if(mPopup)
        {
            mPopup->close();
            delete mPopup;
        }

        std::cout << "[BoardSnapshot>>eventFilter] MouseButtonDblClick  create boardcontains widget ... " << std::endl;

        QMap<QString, QString> param_qmap =
        {
            {"boardcodeqstr", board_code_qstr},
            {"sectorqstr", "cyb"},
            {"maskdateqstr", ""},
            {"newwindowqstr", "true"}
        };

        mPopup = new QWidget();

        //param_qmap = {};
        CandleBoardContains *popupboardcontains = new CandleBoardContains(mPopup, param_qmap);
        popupboardcontains->setSizePolicy(QSizePolicy:: Expanding, QSizePolicy:: Expanding);

        qDebug() << "[BoardSnapshot>>eventFilter] MouseButtonDblClick create boardcontains lay: " << board_code_qstr; //

        QHBoxLayout *candlesticklay = new QHBoxLayout();
        candlesticklay->addWidget(popupboardcontains);

        qDebug() << "[BoardSnapshot>>eventFilter] MouseButtonDblClick create mPopup: " << board_code_qstr; //

        mPopup->setLayout(candlesticklay);

        mPopup->show();


        //return false;//进入下一事件
        return QWidget::eventFilter(obj, qevt);
    }

    if (qevt->type() == QEvent::MouseMove) { //MouseButtonDblClick
        return false;//进入下一事件
    }

    //return false; //false 继续进入下一事件
    return QWidget::eventFilter(obj, qevt);
}



