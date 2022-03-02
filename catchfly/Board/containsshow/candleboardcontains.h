#ifndef CANDLEBOARDCONTAINS_H
#define CANDLEBOARDCONTAINS_H

#include <QWidget>
#include <QObject>
//#include "QWidgetsListWidget.h"
#include <QScrollArea>
#include <QStackedWidget>
#include <QMap>



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

private slots:

private:
    Ui::CandleBoardContains *ui;
    QWidget* m_popup = Q_NULLPTR;


    QLayout* onewdtlay = Q_NULLPTR;
    QLayout* m_plotslay = Q_NULLPTR;
    QWidget* m_anotherwdt = Q_NULLPTR;

    QScrollArea* scrollarea = Q_NULLPTR;
    QStackedWidget* stackedwdt = Q_NULLPTR;

    double m_width = 1205;
    double m_height = 610;

};

#endif // CANDLEBOARDCONTAINS_H
