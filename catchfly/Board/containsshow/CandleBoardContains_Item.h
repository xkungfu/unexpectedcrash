#ifndef CANDLEBOARDCONTAINS_ROW_H
#define CANDLEBOARDCONTAINS_ROW_H

#include "QWidgetsListWidgetDisplay.h"

namespace Ui {
class CandleBoardContains_Item;
}

class CandleBoardContains_Item : public QWidgetsListWidgetDisplay
{
    Q_OBJECT

    public:
        explicit CandleBoardContains_Item(QListWidgetItem *listItem);
        ~CandleBoardContains_Item();
        bool eventFilter(QObject *obj, QEvent *event);
        //void resizeEvent(QResizeEvent *event) override;

    signals:
        void change_fav_FROMITEM(QObject *obj);
        void new_candle_FROMITEM(QObject *obj);

    public slots:
        virtual void dataChanged() override;
        void testplotdoubleclick(QMouseEvent *event);

    private:
        Ui::CandleBoardContains_Item *ui;
        void clickedGraph(QObject *qobj, QMouseEvent *event);
        void handle_candle_clicked(QObject *qobj);
        //double parent_oldwidth;
        //double parent_oldheight;

};

#endif // CANDLEBOARDCONTAINS_ROW_H
