#ifndef CANDLEBOARDCONTAINS_LIST_H
#define CANDLEBOARDCONTAINS_LIST_H

#include <QObject>
#include "QWidgetsListWidget.h"
#include <QVBoxLayout>
#include "settingeditor.h"

class CandleBoardContains_List : public QWidgetsListWidget
{
    Q_OBJECT
public:
    explicit CandleBoardContains_List(QWidget *parent = 0);
    void isinFav(QString tickerqstr, QString favfilename);
    void rowsInserted(const QModelIndex &parent, int start, int end) override;
    QSharedPointer<QSettings> settings = (new SettingEditor)->makeConsumer();

signals:

public slots:
    void showpopup_favorite_ATLIST(QObject *candleobj);
    void change_fav();
    void showpopup_candle_ATLIST(QObject *candleobj);

protected slots:
    virtual QWidgetsListWidgetDisplay *createDisplay(QListWidgetItem *listItem) const override;
    //virtual void wheelEvent(QWheelEvent *event) override;
    void reload_popup();
    //void delete_popup();
private:
    QWidget* mPopup = nullptr;
    QObject* mCandleobj;
    QVBoxLayout* poplay;
};

#endif // CANDLEBOARDCONTAINS_LIST_H
