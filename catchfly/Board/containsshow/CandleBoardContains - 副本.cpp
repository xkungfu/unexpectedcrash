#include "CandleBoardContains.h"
#include "ui_CandleBoardContains.h"

#include <QDebug>
#include <QList>
#include "utils.hpp"
#include "global.h"
#include "flowlayout.h"
#include "section.h"
#include "redispp_ptr.h"
//#include "settingsmanager.h"


#include <wsjcpp_core.h>
#include <wsjcpp_yaml.h>

#include "qcustomplot.h"

#include "Popup/popup_floattool.h"
#include "CandleList/container/CandleContainer.h"

CandleBoardContains::CandleBoardContains(QWidget *parent, QMap<QString, QString> param_qmap) :
    //QWidgetsListWidget(parent),
    ui(new Ui::CandleBoardContains)
{
    ui->setupUi(this);
    //尝试接收mpopup关闭事件：
    //parent->installEventFilter(this);


    //加载板块列表，行业板块：
    FlowLayout *flowlay1 = new FlowLayout();

    for(auto el : global.BOARDINFO_INDUSTRY_QLIST)
    {
        QString current_board_code_qstr = el.first;
        QString current_board_name_qstr = el.second;

        QPushButton* btn = new QPushButton(this);
        btn->setText(current_board_name_qstr);
        btn->setObjectName(current_board_code_qstr);
        //int textwith = board_name_str.length() * 100;
        //btn->setMaximumSize(textwith, 33);
        //btn->setMinimumHeight(88);
        flowlay1->addWidget(btn);

        connect(btn, SIGNAL(clicked()), this, SLOT(at_candleboardcontains_board_button_clicked()));
    }

    QWidget* flowwdt1 = new QWidget();
    flowwdt1->setLayout(flowlay1);
    flowwdt1->setMinimumHeight(55);
    flowwdt1->setMaximumHeight(90);

    //分隔线：
    QFrame *line;
    line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setLineWidth(1);

    //加载板块列表，概念板块：
    FlowLayout* flowlay2 = new FlowLayout();
    for(auto el : global.BOARDINFO_CONCEPT_QLIST){
        QString current_board_code_qstr = el.first;
        QString current_board_name_qstr = el.second;

        QPushButton* btn = new QPushButton(this);
        btn->setText(current_board_name_qstr);
        btn->setObjectName(current_board_code_qstr);
        //int textwith = board_name_str.length() * 100;
        //btn->setMaximumSize(textwith, 33);

        flowlay2->addWidget(btn);

        connect(btn, SIGNAL(clicked()), this, SLOT(at_candleboardcontains_board_button_clicked()));
    }

    QWidget* flowwdt2 = new QWidget();
    flowwdt2->setLayout(flowlay2);
    flowwdt2->setMinimumHeight(55);
    flowwdt2->setMaximumHeight(330);

    QVBoxLayout* boardlistlay = new QVBoxLayout();
    boardlistlay->addWidget(flowwdt1);
    boardlistlay->addWidget(line);
    boardlistlay->addWidget(flowwdt2);

    //为widget添加layout以便使section可以添加boardlistlay:
    QVBoxLayout* boardtoplay = new QVBoxLayout();
    boardtoplay->setContentsMargins(0, 0, 0, 0);
    ui->boardlistwdt->setLayout(boardtoplay);
    //ui->boardlistwdt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);



    Section* section = new Section("test section", 111, ui->boardlistwdt);
    ui->boardlistwdt->layout()->addWidget(section);
    //ui->boardlistwdt->setMinimumHeight(444);
    section->setContentLayout(*boardlistlay);
    section->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    section->setMinimumHeight(444);

    //折叠/展开时，控制操作按钮模块显示或隐藏：
    //connect(section, &Section::section_toggled, [this](){ui->toolpanelwdt->hide();}
    connect(section, SIGNAL(section_toggled(bool)), this, SLOT(at_candleboardcontains_expand_triggered(bool))); //ui->toolpanelwdt->hide();

    //解析参数：
    bool isnewwindow = param_qmap.value("newwindowqstr") == "true" ? true : false;

    qDebug() << "[CandleBoardContains>>CandleBoardContains] param_qmap: " << param_qmap; //param_qmap:  QMap(("boardcodeqstr", "BK1043")("maskdateqstr", "2022-02-28")("newwindowqstr", "true")("sectorqstr", "cyb"))
    //qDebug() << "[CandleBoardContains>>CandleBoardContains] isnewwindow: " << isnewwindow;// true
    if(!param_qmap.empty())
    {
        switch_candlelist(param_qmap);
    }

    //是否在新窗口打开本页面：
    if(isnewwindow)
    {
        PopupFloatTool *popupfloattool = new PopupFloatTool(this, param_qmap);
        popupfloattool->setStyleSheet("background-color: yellow; border: 2px solid green; "); //
        popupfloattool->setMinimumSize(120, 33);
        popupfloattool->setMaximumSize(120, 33);
        popupfloattool->setContentsMargins(0, 0, 0, 0);

        auto toollay = new QHBoxLayout();
        toollay->setContentsMargins(0, 0, 0, 0);
        toollay->addWidget(popupfloattool);
        ui->toolpanelwdt->setLayout(toollay);


        connect(popupfloattool, SIGNAL(change_mask(int)), this, SLOT(change_children_mask(int)));
    }

}

CandleBoardContains::~CandleBoardContains()
{
    qDebug()<< "[CandleBoardContains>>~CandleBoardContains] delete: " <<__LINE__<<__FUNCTION__;
    delete ui;
}

//bool CandleBoardContains::eventFilter(QObject *obj, QEvent *qevt)
//{
//    //qDebug() << "[CandleBoardContains>>eventFilter] objectName: " << obj->objectName();//
//    //qDebug() << "[CandleBoardContains>>eventFilter] qevt: " << qevt;//

//}


//void CandleBoardContains::closeEvent(QCloseEvent *event)
//{
//    qDebug() << "[CandleBoardContains>>closeEvent] event: " << event;//

//    return QWidget::closeEvent(event);
//}

//https://stackoverflow.com/questions/47625754/executing-dynamically-created-buttons
void CandleBoardContains::at_candleboardcontains_board_button_clicked()
{
    QPushButton *b = qobject_cast<QPushButton *>(sender());
    //qDebug() << "[CandleBoardContains>>at_candleboardcontains_board_button_clicked] b->text(): " << b->text();// "船舶制造"
    //qDebug() << "[CandleBoardContains>>at_candleboardcontains_board_button_clicked] b->text().toLatin1().data(): " << b->text().toLatin1().data(); // ????
    //qDebug() << "[CandleBoardContains>>at_candleboardcontains_board_button_clicked] b->objectName(): " << b->objectName(); //"BK0729"
    //qDebug() << "[CandleBoardContains>>at_candleboardcontains_board_button_clicked] b->objectName().toLatin1().data(): " << b->objectName().toLatin1().data(); //BK0729

    //异步调用，参考：Qt invokeMethod 异步调用 - 简书 https://www.jianshu.com/p/c77e28a81708
    //QMetaObject::invokeMethod(this, b->objectName().toLatin1().data());
    //QMetaObject::invokeMethod(this, "switch_candlelist", Qt::QueuedConnection, Q_ARG(QString, fullpath));

    QMap<QString, QString> param_qmap =
    {
        {"boardcodeqstr", b->objectName()},
        {"sectorqstr", "cyb"},
        {"maskdateqstr", QString::fromStdString(date_plus(get_last_trade_date(), 10))},
    };
    switch_candlelist(param_qmap);
}


//#include <sys/stat.h> //用于文件是否存在

//获取股票列表，添加到scan_result (可在软件启动时自动加载一些重点观察的股票)
//std::vector<std::string> tickerlist{"300260", "300444", "300204", "301018", "300319", "300418", "300709", "300317", "300880", "300503", "300217"};
//std::vector<std::string> tickerlist{"300260,300503"};
//int index = rand() % tickerlist.size(); // pick a random index
//std::string tickerstr = tickerlist[index]; // a random value taken from that list
//[CandleScan>>switch_candlelist] path:  "I:\\StockWork\\fomula_result\\scan_recnet_overflow_limited_high_result.txt"
//检查文件修改时间： https://stackoverflow.com/questions/40504281/c-how-to-check-the-last-modified-time-of-a-file
void CandleBoardContains::switch_candlelist(QMap<QString, QString> param_qmap)
{

    //qDebug() << "[CandleBoardContains>>switch_candlelist] param_qmap: " << param_qmap;
    //清空qlistwidget原有的qcustomplot图表：
    //ui->listWidget->clear();

    //解析参数：
    QString board_code_qstr = param_qmap["boardcodeqstr"];

    QString mask_date_qstr_default = settings->value("BOARDCONTAINS_MASK_DATE").toString(); //
    QString mask_date_qstr = param_qmap.value("maskdateqstr").length() > 0 ? param_qmap.value("maskdateqstr") : mask_date_qstr_default; //

    QString begin_qstr = settings->value("BOARDCONTAINS_BEGIN").toString(); //
    QString end_qstr = settings->value("BOARDCONTAINS_END").toString(); //
    QString focus_date_qstr = settings->value("BOARDCONTAINS_FOCUS_DATE").toString(); //
    std::string limitstr = std::to_string(get_job_dates_length_between_string(begin_qstr.toStdString(), end_qstr.toStdString()));
    //qDebug() << "[CandleBoardContains>>switch_candlelist] mask_date_qstr: " << mask_date_qstr << " begin_qstr: " << begin_qstr << " end_qstr: " << end_qstr << " focus_date_qstr: " << focus_date_qstr << " limitstr: " << QString::fromStdString(limitstr);

    //fullpath = "I:\\StockWork\\board\\成份股\\BK0493_cyb.txt";

    //提取板块成份股，生成分组的vector：
    //读取成份股文件：
    QMap<QString, QString> boardcontains_qmap = global.BOARDCONTAINSINFO_CYB_QMAP[board_code_qstr];
    //qDebug()<< "[CandleBoardContains>>switch_candlelist] boardcontains_qmap: " << boardcontains_qmap;

    //生成vector:
    QStringList boardcontains_list = boardcontains_qmap.keys();
    //QVector<QString> contains_qvec = boardcontains_list.toVector();
    std::vector<std::string> contains_vec;
    std::transform(boardcontains_list.begin(), boardcontains_list.end(), std::back_inserter(contains_vec), [](const QString &v){ return v.toStdString(); });

    //按预先设定的数量将vector分成多个子vector：
    int candle_column_num = settings->value("CANDLE_COLUMN_NUM").toInt();

    //std::vector<std::vector<std::string>> vec_vecs = split_vec(contains_vec, candle_column_num);

    
    QVBoxLayout * onevlay = new QVBoxLayout ();

    QVector<QJsonObject> qjsons_qvec;
    for (int i=0; i<contains_vec.size(); i++)
    {
        std::string current_tickerstr = contains_vec[i];
        //std::cout << "[CandleBoardContains>>switch_candlelist] contains_vec i: " << i << " current_tickerstr: " <<current_tickerstr << std::endl; //0 current_tickerstr: 301081 // 1 current_tickerstr: 301127

        //将当前组转为json格式以便生成addItem参数：
        QJsonObject tem_json;
        QString maskdatestr = mask_date_qstr.length() > 0 ? mask_date_qstr : "";
        QString beginstr = begin_qstr.length() > 0 ? begin_qstr : "";
        QString endstr = end_qstr.length() > 0 ? end_qstr : "";
        QString focusdatestr = focus_date_qstr.length() > 0 ? focus_date_qstr : "";
        //QString limitstr = limitstr.length() > 0 ? limitstr : "";

        QJsonObject temp_json;
        //向每个candle传递的参数在此设置：
        temp_json.insert("tickerqstr", QString::fromStdString(current_tickerstr));
        temp_json.insert("beginqstr", beginstr);
        temp_json.insert("endqstr", endstr);
        temp_json.insert("focusdateqstr", focusdatestr);
        temp_json.insert("maskdateqstr", maskdatestr);

        qjsons_qvec.append(temp_json);

    }
    //std::cout << std::endl;

    //qDebug() << "[CandleBoardContains>>switch_candlelist] qjsons_qvec: " << qjsons_qvec; //
    CandleContainer* cbclist = new CandleContainer(this, qjsons_qvec);
    onevlay->addWidget(cbclist);

    auto oldlay = ui->onewdt->layout();
    //qDebug() << "[CandleBoardContains] oldlay: " << oldlay;

    if(oldlay){
        qDebug() << "[CandleBoardContains] delete children of oldlay: " << oldlay;
        //qDeleteAll(ui->onewdt->findChildren<QWidget *>(QString()));
        qDeleteAll(ui->onewdt->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
        delete oldlay;
    }

    onevlay->setContentsMargins(0, 0, 0, 0); //有效
    onevlay->setSpacing(0);//暂不明
    ui->onewdt->setContentsMargins(0, 0, 0, 0);//无效
    ui->onewdt->setLayout(onevlay);

    return;
} //switch_candlelist


//槽函数，切换操作按钮显示或隐藏：
void CandleBoardContains::at_candleboardcontains_expand_triggered(bool expanded) {

    if(expanded){
        ui->toolpanelwdt->hide();
    } else {
        ui->toolpanelwdt->show();
    }

}

void CandleBoardContains::change_children_mask(int xvalue) {

    //qDebug() << "[CandleBoardContains>>find_qlistwidgetitems] xvalue: " << xvalue; //

    CandleContainer* candlecontainer = ui->onewdt->findChild<CandleContainer *>(QString());
    //qDebug() << "[find_qlistwidgetitems] xlist: " << xlist; //QObject(0x2279cc4bcd0)

    //查找QListWidgetItem：
    //QList<QListWidgetItem*> items = xlist->findItems(QString("*"), Qt::MatchWrap | Qt::MatchWildcard);
    //qDebug() << "[find_qlistwidgetitems] xlist items: " << items; //QListWidgetItem:  (0x23cdb056490, 0x23cda912fc0, 0x23cda83a2c0)
    //for (int i = 0; i < items.size(); i++)
    //{
    //    QListWidgetItem* item = items[i];
    //    qDebug() << "[find_qlistwidgetitems] items item: " << item; //0x24c5f716c40
    //}
    //for(auto it : items)
    //{
    //    qDebug() << "[find_qlistwidgetitems] it: " << it;
    //}

    //查找QCustomPlot：
    QList<QCustomPlot*> qcpplots = candlecontainer->findChildren<QCustomPlot *>(QString());
    //qDebug() << "[find_qlistwidgetitems] xlist qcpplots: " << qcpplots; //(QCustomPlot(0x2885c2c8e40, name="601989"), QCustomPlot(0x2885c3dcd70, name="600072"), QCustomPlot(0x2885c3dc670, name="601890"), QCustomPlot(0x2885c3dc830, name="600150"), QCustomPlot(0x2885c3ddd30, name="600685"))
    for (int i = 0; i < qcpplots.size(); i++)
    {
        QCustomPlot* current_qcpplot = qcpplots[i];
        //qDebug() << "[find_qlistwidgetitems] current_qcpplot: " << current_qcpplot; //QCustomPlot(0x2e487409a40, name="601989")
        QList<QCPItemRect*> qcprects = current_qcpplot->findChildren<QCPItemRect *>(QString());
        //qDebug() << "[find_qlistwidgetitems] qcprects: " << qcprects; //(QCPItemRect(0x2e48cd63030)) 或 (QCPItemRect(0x17b84d39340, name = "rect_mask"))
        for (int i = 0; i < qcprects.size(); i++)
        {
            QCPItemRect* current_qcprect = qcprects[i];
            //qDebug() << "[find_qlistwidgetitems] current_qcprect: " << current_qcprect; //QCPItemRect(0x17b84d39340, name = "rect_mask")
            //qDebug() << "[find_qlistwidgetitems] current_qcprect: " << current_qcprect->objectName(); //"rect_mask"
            //qDebug() << "[find_qlistwidgetitems] current_qcprect: " << current_qcprect->layer(); // QCPLayer(0x17b84b87980)
            //qDebug() << "[find_qlistwidgetitems] current_qcprect: " << current_qcprect->layer()->objectName(); //""
            //qDebug() << "[find_qlistwidgetitems] current_qcprect: " << current_qcprect->topLeft->coords(); //QPointF(223.5,12.74)
            if(current_qcprect->objectName() == "rect_mask"){
                double x = current_qcprect->topLeft->coords().x() + xvalue;
                qDebug() << "[find_qlistwidgetitems] rect_mask x: " << x; //
                //重设坐标执行移动，并重载图层：
                current_qcprect->topLeft->setCoords(x, current_qcprect->topLeft->coords().y());
                //qcprect4->setSelectedBrush(QBrush(QColor(222, 1, 1)));
                //current_qcprect->setBrush(QBrush(QColor(19, 222, 222)));
                current_qcprect->layer()->replot();
            }
        }
    }
    return;
}
