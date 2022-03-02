#include "CandleBoardContains_List.h"
#include "CandleBoardContains_Item.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QPushButton>

#include <QListWidget>
#include <QEvent>
#include <QWheelEvent>
#include "utils.hpp"
#include "global.h"

#include "Popup/popup_favlist.h"
#include "Plot/CandleContainerSingle.h"

CandleBoardContains_List::CandleBoardContains_List(QWidget *parent) : QWidgetsListWidget(parent)
{

}

/*
[CandleBoardContains_List>>createDisplay] listItem:  0x10be1660
[CandleBoardContains_List>>createDisplay] listItem sizeHint:  QSize(-1, -1)

[CandleScan_Item>>dataChanged] plotcontainer size:  QSize(382, 282)
[CandleScan_Item>>dataChanged] plotcontainer size:  QSize(18, 18)
*/

//在此函数内修改 QWidgetsListWidget::rowsInserted 添加的 QListWidgetItem
QWidgetsListWidgetDisplay *CandleBoardContains_List::createDisplay(QListWidgetItem *listItem) const
{
    //qDebug() << "[CandleBoardContains_List>>createDisplay] listItem: " << listItem; //0xdb3b230
    //qDebug() << "[CandleBoardContains_List>>createDisplay] listItem sizeHint: " << listItem->sizeHint(); //QSize(-1, -1)
    //qDebug() << "[CandleBoardContains_List>>createDisplay] listItem Type: " << listItem->Type; //0

    int height_default = settings->value("CANDLE_HEIGHT").toInt();
    //qDebug() << "[CandleBoardContains_List>>createDisplay] height_default: " << height_default; //如果没设置，为0.

    int height = height_default ? height_default : 555;
    listItem->setSizeHint(QSize(0, height));
    //listItem->setTextAlignment(444);??
    //listItem->setBackground(Qt::red);




    return new CandleBoardContains_Item(listItem);
}


////鼠标滚轮事件：//使用此函数可覆盖 QWidgetsListWidget wheelEvent
//void CandleBoardContains_List::wheelEvent(QWheelEvent *event)
//{
//    // to do any processing here if you want to do something before scrolling
//    //qDebug() << "[CandleBoardContains_List>>wheelEvent] event 1: " << event;

//    // call base implementation
//    //QListWidget::wheelEvent(event);  //报错  error: call to non-static member function without an object argument error: 'wheelEvent' is a protected member of 'QListView'

//    // to do some processing after scrolling.
//    //qDebug() << "[CandleBoardContains_List>>wheelEvent] event 2: " << event;

//}


//使用此函数可覆盖 QWidgetsListWidget rowsInserted
void CandleBoardContains_List::rowsInserted(const QModelIndex &parent, int start, int end)
{
    //qDebug() << "[CandleBoardContains_List>>rowsInserted] start: " << start; //10
    //qDebug() << "[CandleBoardContains_List>>rowsInserted] end: " << end; //10

    for (int row = start; row <= end; ++row) {

        //qDebug() << "[CandleBoardContains_List>>rowsInserted] row: " << row; //10

        //item函数来自文件：qlistwidget.h: QListWidgetItem *item(int row) const;
        auto listItem = item(row);
        Q_ASSERT(listItem != nullptr);

        if(itemWidget(listItem) == nullptr) {

            //1 没有设置setSizeHint的widget无法显示 2 放置在createDisplay之前或之内，不要放在之后，防止二次触发datachanged
            //listItem->setSizeHint(QSize(666, 550)); //widget->sizeHint() 输出 QSize(100, 389)

            // setItemWidget passes ownership to List's viewport
            //调用List>>createDisplay函数创建控件：
            auto widget = createDisplay(listItem);

            //调出收藏夹列表弹窗：
            QObject::connect(widget, SIGNAL(change_fav_FROMITEM(QObject*)), this, SLOT(showpopup_favorite_ATLIST(QObject*)));

            //调出独立K线图弹窗：
            QObject::connect(widget, SIGNAL(new_candle_FROMITEM(QObject*)), this, SLOT(showpopup_candle_ATLIST(QObject*)));

            //调用QListWidget>>setItemWidget: 第一次触发[CandleBoardContains_List>>dataChanged] 将 widget 插入 listItem 也触发了[Display>>datachanged]且传递了addItem的参数
            setItemWidget(listItem, widget);

            //以下留空：
            //此处对listItem的设置,将第二次触发[CandleBoardContains_List>>dataChanged] 也触发了[Display>>datachanged]且传递了addItem的参数

        }
    }

    QListWidget::rowsInserted(parent, start, end);

}

//方案2：动态自定义收藏窗口，点击K线图收藏按钮触发：
void CandleBoardContains_List::showpopup_favorite_ATLIST(QObject *candleobj){

    qDebug() << "[CandleBoardContains_List>>showpopup_favorite_ATLIST] candleobj: " << candleobj->objectName(); // "300945"
    qDebug() << "[CandleBoardContains_List>>showpopup_favorite_ATLIST] mPopup: " << mPopup; //

    mCandleobj = candleobj;

    if(mPopup)
    {
        mPopup->close();
        //delete mPopup;
    }

    auto button = new QToolButton(mPopup);
    button->setObjectName(candleobj->objectName());//此值将传入收藏夹弹窗
    PopupFavlist *popupfav = new PopupFavlist(button, mPopup);
    popupfav->setStyleSheet("background-color: yellow; border: 2px solid rgb(222, 20, 7); "); //
    popupfav->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    auto favlay = new QHBoxLayout();
    favlay->addWidget(popupfav);

    mPopup = new QWidget();
    mPopup->setLayout(favlay);
    mPopup->setMinimumSize(444, 666);
    mPopup->show();

    connect(popupfav, SIGNAL(send_change_fav_finished_ATPOPUPFAVLIST()), SLOT(reload_popup()));
}



void CandleBoardContains_List::showpopup_candle_ATLIST(QObject *candleobj){

    //qDebug() << "[CandleBoardContains_List>>showpopup_candle_ATLIST] candleobj: " << candleobj->objectName(); // "300945"
    //qDebug() << "[CandleBoardContains_List>>showpopup_candle_ATLIST] mPopup: " << mPopup; //QWidget(0x22fed92c660) 或 QWidget(0x0)

    if(mPopup)
    {
        mPopup->close();
        //delete mPopup;
    }

    if(candleobj->objectName().length() > 0)
    {
        std::string tickerstr = candleobj->objectName().toStdString();

        std::map<std::string, std::string> candlesinglemap =
        {
            {"tickerstr", tickerstr},
            //{"beginstr", "2020-12-24"},
            //{"endstr", "2022-01-29"},
            //{"focusdatestr", "2021-11-22"},
            {"maskdatestr", get_last_trade_date()},
            //{"scalestr", "1"},
        };
        CandleContainerSingle *popupcandlesingle = new CandleContainerSingle(mPopup, candlesinglemap);
        popupcandlesingle->setSizePolicy(QSizePolicy:: Expanding, QSizePolicy:: Expanding);

        QHBoxLayout *candlesticklay = new QHBoxLayout();
        candlesticklay->addWidget(popupcandlesingle);

        mPopup = new QWidget();
        mPopup->setLayout(candlesticklay);
        mPopup->show();
    }
}

void CandleBoardContains_List::change_fav(){
    qDebug() << "[CandleBoardContains_List>>change_fav] ... ";
    auto button = qobject_cast<QPushButton *>(sender());
    qDebug() << "[CandleBoardContains_List>>change_fav] button- " << button->objectName();
    qDebug() << "[CandleBoardContains_List>>change_fav] button- " << button->text();
    qDebug() << "[CandleBoardContains_List>>change_fav] button- " << button->property("inside");

    bool isinfav = is_str_in_file(button->objectName().toStdString(), global.FAV_PATH + "\\" + button->text().toStdString() + ".txt");
    qDebug() << "[CandleBoardContains_List>>change_fav] isinfav: " << isinfav;

    if(isinfav){
        //移除:
        remove_str_from_file(button->objectName().toStdString(), global.FAV_PATH + "\\" + button->text().toStdString() + ".txt");
    } else {
        append_str_into_file(button->objectName().toStdString(), global.FAV_PATH + "\\" + button->text().toStdString() + ".txt");
    }
}


void CandleBoardContains_List::reload_popup(){
    showpopup_favorite_ATLIST(mCandleobj);
}

//void CandleBoardContains_List::delete_popup(){
//    delete mPopup;
//    mPopup = nullptr;
//}
