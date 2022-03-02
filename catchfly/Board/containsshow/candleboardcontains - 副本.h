#ifndef CANDLEBOARDCONTAINS_H
#define CANDLEBOARDCONTAINS_H

#include <QWidget>
#include <QObject>
//#include "QWidgetsListWidget.h"

//#include "CandleBoardContains_List.h"
#include "Setting/settingeditor.h"

namespace Ui {
    class CandleBoardContains;
}

class CandleBoardContains : public QWidget
{
    Q_OBJECT
public:
    //explicit CandleBoardContains(QWidget *parent = 0);
    explicit CandleBoardContains(QWidget *parent = 0,  QMap<QString, QString> qmap = {});
    ~CandleBoardContains();

signals:

public slots:
    void switch_candlelist(QMap<QString, QString> param_qmap);
    void at_candleboardcontains_expand_triggered(bool expanded);
    void change_children_mask(int xvalue = 0);
    void at_candleboardcontains_board_button_clicked();

private slots:

private:
    Ui::CandleBoardContains *ui;
    //CandleBoardContains_List* cbclist = new CandleBoardContains_List();
    //void closeEvent(QCloseEvent *event) override;
    //bool eventFilter(QObject *obj, QEvent *qevt) override;

    QSharedPointer<QSettings> settings = (new SettingEditor)->makeConsumer();
    //qDebug() << "[CandleBoardContains>>on_board_button_clicked] settings: " << settings; // QSharedPointer(QSettings(0x201f064f160))
    //qDebug() << "[CandleBoardContains>>on_board_button_clicked] settings: " << settings.get()->allKeys(); //("BOARDFOCUSDATE", "BOARDS_LIST_SECTOR", "BOARDS_RANK_FILE", ... ... , "Testcustomgroup/xtest")
    //qDebug() << "[CandleBoardContains>>on_board_button_clicked] settings: " << settings->value("BOARDS_RANK_FILE"); //QVariant(QString, "I:\\StockWork\\board\\东方财富.txt")
    QWidget* m_popup = Q_NULLPTR;


};

#endif // CANDLEBOARDCONTAINS_H
