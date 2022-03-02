 #include "CandleBoardContains_Item.h"
#include "ui_CandleBoardContains_Item.h"

#include <QDebug>
#include <QWidget>
#include <QHBoxLayout>
#include <QWheelEvent>

#include "qcustomplot.h"
//#include "CandleBase.h"
#include "Plot/CandleCreatorJ.h"
#include "Plot/CandleCreatorDF.h"

#include <string>
#include <vector>
#include <sstream>
#include "global.h"
//#include "popup_limituppatternlist.h"


//QListWidgetItem Class | Qt Widgets 5.15.7 https://doc.qt.io/qt-5/qlistwidgetitem.html
/*
QListWidgetItem(const QListWidgetItem &other)
QListWidgetItem(const QIcon &icon, const QString &text, QListWidget *parent = nullptr, int type = Type)
QListWidgetItem(const QString &text, QListWidget *parent = nullptr, int type = Type)
QListWidgetItem(QListWidget *parent = nullptr, int type = Type)
*/

CandleBoardContains_Item::CandleBoardContains_Item(QListWidgetItem *listItem) :
    QWidgetsListWidgetDisplay(listItem),
    ui(new Ui::CandleBoardContains_Item)
{
    //qDebug() << "[CandleBoardContains_Item>>CandleBoardContains_Item] listItem text: " << listItem->text();
    //[CandleBoardContains_Item>>CandleBoardContains_Item] listItem text:  "test addItem params number: 0 !"

    ui->setupUi(this);
    //无效：ui->plotcontainer->setMinimumSize(100, 600);
    //ui->plotcontainer->setSizeHint(QSize(100, 600)); // no member named 'setSizeHint' in 'QWidget'
    //ui->plotcontainer->setStyleSheet("background-color: green;");
    //qDebug() << "[CandleBoardContains_Item>>CandleBoardContains_Item] 2 ... ";

}

CandleBoardContains_Item::~CandleBoardContains_Item()
{
    delete ui;
}

//由 QWidgetsListWidget::rowsInserted 触发

//重复执行的问题： listWidget->addItem 触发[QWidgetsListWidget>>rowsInserted] 》==》 [List>>createCandleBoardContains_Item] 》==》 [CandleBoardContains_Item>>CandleBoardContains_Item] 》==》 [QWidgetsListWidget>>dataChanged] [CandleBoardContains_Item>>datachanged]
//解决方案：QWidgetsListWidget::rowsInserted 中对listItem的设置导致重复执行，如：listItem->setSizeHint(QSize(100, 389)); 将此类设置提前到createDisplay之前，可以避免重复执行。
//每次触发dataChanged，将会重新设置本函数调用的 widget, 如果此 widget 又重新添加了布局 layout， 将导致报错：QWidget::setLayout: Attempting to set QLayout "" on QWidget "plotcontainer", which already has a layout
//解决方案1 qt remove widget from layout: 检查ui->plotcontainer->是否已经存在layout, 如果存在则使用原layout. 并且装入新widget前，需要删除旧的widget
//解决方案2 qt replace layout of widget: 检查ui->plotcontainer->是否已经存在layout, 如果存在则新建新的layout，然后装入新的widget，然后使用新的layout替换旧的layout.

//解决方案1 qt remove widget from layout: 检查ui->plotcontainer->是否已经存在layout, 如果存在则使用原layout. 并且装入新widget前，需要删除旧的widget
////问题1-1： 此方案中 ui->plotcontainer->setMinimumSize ui->plotcontainer->setStyleSheet 等设置会导致鼠标滚轮失效 QCustomPlot qslot->setMinimumSize(111, 333)不起作用。
void CandleBoardContains_Item::dataChanged()
{

    // 布局处理 -------------------------------------------------------------------------------------------

    //获取父级widget的布局，以便根据布局名称删除其中的 widget:
    if(!ui->plotcontainer->layout()){
        QHBoxLayout *lay = new QHBoxLayout();
        ui->plotcontainer->setLayout(lay);
    }
    QLayout *plotcontainerlay = ui->plotcontainer->layout();
    plotcontainerlay->setAlignment(Qt::AlignLeft | Qt::AlignTop);

//    //单次删除1个：
//    QWidget *oldwidget = ui->plotcontainer->findChild<QWidget*>();
//    plotcontainerlay->removeWidget(oldwidget);
//    oldwidget->deleteLater();

    //删除所有：
//    QList<QWidget *> oldwidgetList= ui->plotcontainer->findChildren<QWidget *>();
//     for(int i=0;i<oldwidgetList.length();++i)
//     {
//         QWidget *fm =oldwidgetList.at(i);
//         plotcontainerlay->removeWidget(fm);
//         fm->deleteLater();
//     }

     //qDeleteAll(ui->plotcontainer->findChildren<QWidget *>(QString(), Qt::FindDirectChildrenOnly));
     qDeleteAll(ui->plotcontainer->findChildren<QWidget *>(QString()));


     // 参数处理 -------------------------------------------------------------------------------------------

     // 此处参数由 switch_candlelist addItem 传入：每次传入一组tickerstr字符串，格式为： aaaaaa, bbbbbb, cccccc 或 aaaaaa yyyy-mm-dd, bbbbbb yyyy-mm-dd, cccccc yyyy-mm-dd,
     QString item_qstr = index().data(Qt::DisplayRole).toString();
     //qDebug() << "[CandleBoardContains_Item>>datachanged] item_qstr: " << item_qstr; //"[{\"tickerstr\":\"300670\"},{\"tickerstr\":\"300324\"}]"
     std::string item_str = item_qstr.toStdString();

     //解析json:
     nl::json tickersj;
     if(nl::json::accept(item_str)){
         tickersj = nl::json::parse(item_str);
     } else {
         qDebug() << "[CandleBoardContains_Item>>datachanged] ERROR: tickers_str is not json, tickers_str: " << QString::fromStdString(item_str);
         return;
     }

     //循环json, 每个ticker创建一个图表：
      nl::json currenttickerj;
      for (int i=0; i<tickersj.size(); i++ ) {

         currenttickerj = tickersj[i];
         //qDebug() << "[CandleBoardContains_Item>>datachanged] i: " << i << " currenttickerj: " << QString::fromStdString(currenttickerj.dump()); // i:  0  currenttickerj:  "{\"tickerstr\":\"300670\"}"

         if(currenttickerj.is_null()){
             continue;
         }

         std::string tickerstr = currenttickerj.contains("tickerstr") ? currenttickerj["tickerstr"].get<std::string>() : currenttickerj.get<std::string>();
         std::string beginstr = currenttickerj.contains("beginstr") ? currenttickerj["beginstr"].get<std::string>() : "";
         std::string endstr = currenttickerj.contains("endstr") ? currenttickerj["endstr"].get<std::string>() : "";
         std::string limitstr = currenttickerj.contains("limitstr") ? currenttickerj["limitstr"].get<std::string>() : "";
         std::string focusdatestr = currenttickerj.contains("focusdatestr") ? currenttickerj["focusdatestr"].get<std::string>() : "";
         std::string maskdatestr = currenttickerj.contains("maskdatestr") ? currenttickerj["maskdatestr"].get<std::string>() : "";
         std::string scalestr = currenttickerj.contains("scalestr") ? currenttickerj["scalestr"].get<std::string>() : "";

         if(tickerstr.length() > 0)
         {

             //std::string limitstr = get_job_dates_length_between_string(beginstr, endstr) != 0 ? std::to_string(get_job_dates_length_between_string(beginstr, endstr)) : "250";
             std::cout << "[CandleBoardContains_Item>>dataChanged] ticker_str: " << tickerstr << " beginstr: " << beginstr << " endstr: " << endstr << " focusdatestr: " << focusdatestr << " maskdatestr: " << maskdatestr << " limitstr: " << limitstr << std::endl;

             //创建K线蜡烛图：
             QHBoxLayout *candleplotlay = new QHBoxLayout();

             //CandleBase customcandle;
             //auto candleplot = customcandle.setupCandlestick(tickerstr, limitstr, beginstr, endstr, focusdatestr, scalestr);

             std::map<std::string, std::string> param_map =
             {
                 {"tickerstr", tickerstr},
                 {"beginstr", beginstr},
                 {"endstr", endstr},
                 {"limitstr", limitstr},
                 {"focusdatestr", focusdatestr},
                 {"maskdatestr", maskdatestr},
                 {"scalestr", scalestr}
             };


             CandleCreatorDF  customcandle;
             auto candleplot = customcandle.setupCandlestick(param_map);

             //candleplot->setMinimumSize(444, 333);
             //candleplot->setMaximumSize(600, 550);
             //candleplot->setInteractions(QCP::iNone); //QCustomPlot删除全部鼠标事件
             //candleplot->setStyleSheet("background-color: pink;");
             //candleplot->setLayout(candleplotlay);
             //candleplot->setInteractions(QCP::iRangeZoom | QCP::iRangeDrag);//缩放 拖动
             //candleplot->setInteractions(QCP::iRangeDrag);//拖动
             //candleplot->setAttribute(Qt::WA_TransparentForMouseEvents);
             //candleplot->setAttribute(Qt::WA_TransparentForMouseEvents, false);
             //qDebug() << "[CandleBoardContains_Item>>dataChanged] candleplot size： " << candleplot->size();
             //candleplot->setFocus();

             candleplot->setObjectName(QString::fromStdString(tickerstr));
             candleplot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

             candleplot->installEventFilter(this); //添加事件过滤器

             candleplot->setLayout(candleplotlay);
             plotcontainerlay->addWidget(candleplot);
             plotcontainerlay->setAlignment(Qt::AlignLeft | Qt::AlignTop);


/*
            //测试通过坐标获取并控制遮罩:
             QCPAbstractItem *item1 = candleplot->itemAt(QPoint(530,48), false);
             qDebug() << "[CandleBoardContains_Item>>dataChanged] item1: " << item1;//
             QCPAbstractItem *item2 = candleplot->itemAt(QPoint(824,48), false);
             qDebug() << "[CandleBoardContains_Item>>dataChanged] item2: " << item2;//
             if(item1){
                 qDebug() << "[CandleBoardContains_Item>>dataChanged] item1 objectName: " << item1->objectName();//""
                 qDebug() << "[CandleBoardContains_Item>>dataChanged] item1 layer objectName: " << item1->layer()->objectName();//""
                 QCPItemRect *qcprect4 = qobject_cast<QCPItemRect*>(item1);
                 qDebug() << "[CandleBoardContains_Item>>dataChanged] qcprect4 " << qcprect4;//
                 qDebug() << "[CandleBoardContains_Item>>dataChanged] qcprect4 layer objectName" << qcprect4->layer()->objectName(); //""
                 qDebug() << "[CandleBoardContains_Item>>dataChanged] qcprect4 layer objectName" << qcprect4->topLeft;
                 qcprect4->topLeft->setCoords(111, 5);
                 //qcprect4->setSelectedBrush(QBrush(QColor(222, 1, 1)));
                 qcprect4->setBrush(QBrush(QColor(19, 222, 222)));
                 //item1->setSelected(true);
                 item1->layer()->replot();
             }
*/


         }
         //qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer child name 3 2： " << ui->plotcontainer->findChildren<QWidget *>();
    }
    //ui->plotcontainer->setAttribute(Qt::WA_TransparentForMouseEvents); //当前widget添加属性 WA_TransparentForMouseEvents, WA_TransparentForMouseEvents 穿透全部鼠标事件
    //ui->plotcontainer->setAttribute(Qt::WA_TransparentForMouseEvents, false); //当前widget删除属性 WA_TransparentForMouseEvents

    ui->plotcontainer->setObjectName("plotcontainerhascandlechildren");
    ui->plotcontainer->installEventFilter(this); //过滤事件
    ui->plotcontainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer size: " << ui->plotcontainer->size(); //[CandleBoardContains_Item>>dataChanged] plotcontainer size:  QSize(382, 282)
    //qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer sizeHint: " << ui->plotcontainer->sizeHint(); //[CandleBoardContains_Item>>dataChanged] plotcontainer sizeHint:  QSize(18, 18)
}


void CandleBoardContains_Item::clickedGraph(QObject *qobj, QMouseEvent *event)
{

    qDebug() << "[CandleBoardContains_Item>>clickedGraph] " << qobj->objectName();

    QPoint p = event->pos();
    qDebug() << "[CandleBoardContains_Item>>clickedGraph] position: " << p;

    if(p.x() > 124 && p.x() < 166 && p.y() > 2 && p.y() < 60){
        qDebug() << "[clickedGraph] position favorite clicked ... ";
    }
}


void CandleBoardContains_Item::handle_candle_clicked(QObject *qobj)
{
    qDebug() << "[CandleBoardContains_Item>>handle_candle_clicked] " << qobj->objectName();
}


void CandleBoardContains_Item::testplotdoubleclick(QMouseEvent *event)
{
    std::cout << "[CandleBoardContains_Item>>testplotdoubleclick] ++++++++++++++++++++++++++++++++++++ " << std::endl;
    //ev->ignore();
}

//void CandleBoardContains_Item::resizeEvent(QResizeEvent *event)
//{
////    std::cout << "[CandleBoardContains_Item>>resizeEvent] ........................................... ";
////    QWidget::resizeEvent(event);
////    qDebug() << "[CandleBoardContains_Item>>resizeEvent] event: " <<  event->oldSize().width(); //1252
////    int oldWidth = event->oldSize().width();

//    return QWidget::resizeEvent(event);

//}


//鼠标事件过滤，过滤设置在 plotcontainer 时，在 plotcontainer 模块内 qcustomplot 外的夹缝中有效
//过滤设置在 qcustomplot 时， 在 qcustomplot 模块内有效
// 可选事件： 单击：QEvent::MouseButtonPress,  鼠标进入:QEvent::Enter, 鼠标双击:QEvent::MouseButtonDblClick
//qcustomplot 拖动事件： QEvent::MouseButtonPress QEvent::MouseMove QEvent::MetaCall  滚轮事件：QEvent::Wheel

//如果eventFilter返回值为true，则不再调用下一个处理函数event()  if you return true , you will take the event and widget never sees it so be carefull with that.
// false means it should be send to target also. 接着调用event()函数
//event()函数返回true和false已经没有意义了，因为我们假设它是最后一个事件处理函数了
//假如在eventFilter()函数中调用了ignore()，并且返回false，那么event()函数将被紧接着调用，且它收到的事件accept属性为false
//accpet属性对应的accpet()函数和ignore()函数决定的事件传递是在父子对象之间的，而返回值决定的事件传递是在同一目标对象的各个事件处理函数之间的。在各个事件处理函数中都可以调用ignore()和accept()，以最后一个调用这两个函数的事件处理函数设置的accept属性值为最终值
bool CandleBoardContains_Item::eventFilter(QObject *obj, QEvent *qevt)
{
    //qDebug() << "[CandleBoardContains_Item>>eventFilter] objectName: " << obj->objectName();
    //qDebug() << "[CandleBoardContains_Item>>eventFilter] qevt type: " << qevt->type(); //QEvent::Resize

    if (qevt->type() == QEvent::Wheel) { //鼠标滚轮
        //return CandleList::eventFilter(obj, qevt);//传递到父类事件过滤器
        //QApplication::sendEvent(ui->plotcontainer, (QEvent*) qevt);//尝试传递事件到父级...无效。
        //qDebug() << "[CandleBoardContains_Item>>eventFilter] Wheel ... parent obj: " << obj->parent(); //parent obj:  QWidget(0x225d12c0, name = "plotcontainerhascandlechildren")
        //std::cout << "[CandleBoardContains_Item>>eventFilter] Wheel ... parent obj name: " << obj->parent()->objectName().toStdString() << std::endl; //parent obj name: plotcontainerhascandlechildren
        //qDebug() << "[CandleBoardContains_Item>>eventFilter] Wheel ... parent parent obj: " << obj->parent()->parent(); //parent parent obj:  CandleBoardContains_Item(0x221802c0, name = "CandleBoardContains_Item")
        //std::cout << "[CandleBoardContains_Item>>eventFilter] Wheel ... parent parent obj name: " << obj->parent()->parent()->objectName().toStdString() << std::endl; //parent parent obj: CandleBoardContains_Item

        //qevt->accept();
        //qevt->ignore();

        QApplication::sendEvent(obj->parent()->parent()->parent(), qevt);
        //obj->parent()->parent()->event(qevt);

        //return false;
        return false; //进入下一事件
    }

    if (qevt->type() == QEvent::Resize) { //改变尺寸

        return false; //resize条件下如果return true 阻止进入下一事件，可能导致尺寸自动调整失败

        qDebug() << "[CandleBoardContains_Item>>eventFilter] objectName: " << obj->objectName(); //"plotcontainerhascandlechildren" 或 "300317"
        if(obj->objectName() != "plotcontainerhascandlechildren"){
            //QResizeEvent *resizeevent = static_cast<QResizeEvent*>(qevt);
            //qDebug() << "[CandleBoardContains_Item>>eventFilter] event: " <<  resizeevent->oldSize(); //
            //parent_oldwidth = resizeevent->oldSize().width();
            //parent_oldheight = resizeevent->oldSize().height();

            QCustomPlot *qplot =  qobject_cast<QCustomPlot*>(qobject_cast<QObject*>(obj));
            if(qplot){
                qDebug() << "[CandleBoardContains_Item>>eventFilter] objectName: " << qplot->objectName();
                qDebug() << "[CandleBoardContains_Item>>eventFilter]  obj->parent(): " <<  obj->parent(); //QWidget(0x1b09b1da3d0, name = "plotcontainerhascandlechildren")
                QWidget *plotparentwdt =  qobject_cast<QWidget*>(qobject_cast<QObject*>(obj->parent()));
                qDebug() << "[CandleBoardContains_Item>>eventFilter] plotparentwdt width: " << plotparentwdt->width(); //
                qDebug() << "[CandleBoardContains_Item>>eventFilter] plotparentwdt height: " << plotparentwdt->height(); //

                //qplot->setMaximumWidth( plotparentwdt->width() / 2);
                qplot->resize(plotparentwdt->width() / 2 -20, plotparentwdt->height()-15);
                qplot->replot();
            }
        }
    }

    if (qevt->type() == QEvent::MouseButtonPress) { //MouseButtonDblClick
        std::cout << "[CandleBoardContains_Item>>eventFilter] MouseButtonPress objectName: " << obj->objectName().toStdString() << std::endl;

        //要点：QEvent类型没有pos属性 no member named pos in qevent，需要先转换为QMouseEvent:
        QMouseEvent *qmevt = static_cast<QMouseEvent *>(qevt);
        QPoint p = qmevt->pos();
        qDebug() << "[CandleBoardContains_Item>>eventFilter] MouseButtonPress position: " << p;

        //点击收藏：
        if(p.x() > 124 && p.x() < 166 && p.y() > 2 && p.y() < 60){
            qDebug() << "[CandleBoardContains_Item>>eventFilter] MouseButtonPress position favorite clicked ... ";
            //调出收藏弹窗： connect配置在Src\WLIST\QWidgetsListWidget.cpp : QObject::connect(widget, SIGNAL(change_fav_FROMITEM(QObject*)), this, SLOT(showpopup_ATLIST(QObject*)));
            emit change_fav_FROMITEM(obj);
        } else if(p.x() > 166 && p.x() < 208 && p.y() > 2 && p.y() < 60){
            qDebug() << "[CandleBoardContains_Item>>eventFilter] MouseButtonPress position zoom_in clicked ... ";
            //调出独立K线图弹窗：
            emit new_candle_FROMITEM(obj);
        }

        //qevt->accept();
        return false;
    }

    if (qevt->type() == QEvent::MouseButtonDblClick) { //MouseButtonDblClick
        std::cout << "[CandleBoardContains_Item>>eventFilter] MouseButtonDblClick ... " << std::endl;
        std::cout << "[CandleBoardContains_Item>>eventFilter] MouseButtonDblClick objectName: " << obj->objectName().toStdString() << std::endl;
        //qevt->accept();
        return false;//进入下一事件
    }

    if (qevt->type() == QEvent::MouseMove) { //MouseButtonDblClick
        return false;//进入下一事件
        QMouseEvent *qmevt = static_cast<QMouseEvent*>(qevt);
        QPoint p = qmevt->pos();
        //qDebug() << "[CandleBoardContains_Item>>eventFilter] MouseMove position: " << p;

        //鼠标坐标转化为CustomPlot内部坐标. 可据此获取图表qpoint属性值： 参考：  CrossLine::onMouseMoved
        //qDebug() << "[CandleBoardContains_Item>>eventFilter] MouseMove obj: " << obj; //[CandleBoardContains_Item>>eventFilter] MouseMove obj:  QCustomPlot(0x56f5410, name = "300443")
        QCustomPlot *qplot =  qobject_cast<QCustomPlot*>(qobject_cast<QObject*>(obj));
        float x_coord = qplot->xAxis->pixelToCoord(p.x());
        float y_coord = qplot->yAxis->pixelToCoord(p.y());
        //qDebug() << "[CandleBoardContains_Item>>eventFilter] MouseMove x_coord: " << x_coord << " y_coord: " << y_coord;
        return false; //进入下一事件
    }



    //return CandleBoardContains_Item::eventFilter(obj, qevt); 导致无限循环
    //return true; //true 停止进入下一事件
    return false; //false 继续进入下一事件
    //return QWidget::eventFilter(obj, qevt);
}


//////解决方案2 qt replace layout of widget: 检查ui->plotcontainer->是否已经存在layout, 如果存在则新建新的layout，然后装入新的widget，然后使用新的layout替换旧的layout.
//////此方案中delete layout 会导致在其他函数设置的ui->plotcontainer->setStyleSheet等失效，需要重新设置，或者全部集中到本函数内设置。

////问题2-1： 此方案中 ui->plotcontainer->setMinimumSize ui->plotcontainer->setStyleSheet 等设置会导致鼠标滚轮失效 QCustomPlot qslot->setMinimumSize(111, 333)不起作用。
////问题2-2： 此方案中 鼠标放在plot图上时，鼠标滚轮失效。放在plot之间的间隔和scrollbar时正常。
////问题2-3： 此方案中 由于一次addItem触发二次dataChanged， 导致本函数内所有调用的函数都将执行二次，造成widget layout重复添加的问题。
//void CandleBoardContains_Item::dataChanged()
//{
//    QString ticker_qstrxes = index().data(Qt::DisplayRole).toString() + "aabbccdd";
//    qDebug() << "[CandleBoardContains_Item>>datachanged] ticker_qstrxes: " << ticker_qstrxes;
////    ui->label->setText(ticker_qstrxes);

//    qDebug() << "[CandleBoardContains_Item>>datachanged] ui->plotcontainer->layout: " << ui->plotcontainer->layout();

//    QHBoxLayout *newplotlay = new QHBoxLayout();

//    QCustomPlot *candleplot = new QCustomPlot();

//    qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer child name 1： " << ui->plotcontainer->findChildren<QWidget *>();

//    if (ui->plotcontainer->findChild<QCustomPlot*>()) {

//        delete ui->plotcontainer->layout()->widget();

//        //调用蜡烛图配置函数：
//        CandleBase customcandle;
//        customcandle.setupCandlestick(candleplot, "");

//        qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer child name 2 1： " << ui->plotcontainer->findChildren<QWidget *>();

//        qDebug() << "[connect pTableView] stock_candle_switch  2 ...........................";
//        candleplot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//        candleplot->setMinimumSize(100, 222);
//        candleplot->setMaximumHeight(333);

//        newplotlay->addWidget(candleplot);

//        qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer child name 2 2： " << ui->plotcontainer->findChildren<QWidget *>();

//    } else {
//        qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer child name 3 1： " << ui->plotcontainer->findChildren<QWidget *>();

//        //调用蜡烛图配置函数：
//        CandleBase customcandle;
//        customcandle.setupCandlestick(candleplot, "");

//        qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer child name 3 2： " << ui->plotcontainer->findChildren<QWidget *>();

//        qDebug() << "[connect pTableView] stock_candle_switch  2 ...........................";
//        candleplot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//        candleplot->setMinimumSize(100, 222);
//        candleplot->setMaximumHeight(333);

//        newplotlay->addWidget(candleplot);

//    }

//    //ui->plotcontainer->setWidget(qslot); 'class QCustomPlot' has no member named 'setWidget'

//    //ui->plotcontainer->setLayout(newplotlay);//每次触发dataChanged，将会重新设置本函数调用的 widget, 如果此 widget 又重新设置了布局 layout， 将导致报错：QWidget::setLayout: Attempting to set QLayout "" on QWidget "plotcontainer", which already has a layout
//    //ui->plotcontainer->layout()->destroyed(); Missing emit keyword on signal call QObject::destroyed [clazy-incorrect-emit]
//    if(ui->plotcontainer->layout()){
//        delete ui->plotcontainer->layout();
//    }

//    qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer child name 4： " << ui->plotcontainer->findChildren<QWidget *>();


////    ui->plotcontainer->setMinimumSize(100, 100);
////    ui->plotcontainer->setStyleSheet("background-color: green;");


//    ui->plotcontainer->setLayout(newplotlay);



//    qDebug() << "[CandleBoardContains_Item>>dataChanged] plotcontainer child name 5： " << ui->plotcontainer->findChildren<QWidget *>();
//    //[CandleBoardContains_Item>>dataChanged] plotcontainer child name 5：  (QCustomPlot(0x38cf810), QCustomPlot(0xaf43010))


//}



