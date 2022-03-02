#ifndef BoardSnapshot_H
#define BoardSnapshot_H

#include <QWidget>
#include <map>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QStackedWidget>
#include <QMutex>

#include "global.h"




class QLabel;

namespace Ui {
    class BoardSnapshot;
}

class BoardSnapshot : public QWidget
{
    Q_OBJECT
    public:
        explicit BoardSnapshot(QWidget *parent = nullptr);
        //explicit BoardSnapshot(QWidget *parent = nullptr, QMap<QString, QString> MyMap = {});
        ~BoardSnapshot();

    bool eventFilter(QObject *obj, QEvent *qevt) override;
    signals:
        void boardsnapshot_close_realtimedata_future();

    public slots:
        void dynamic_update_snapshot(DongfancaifuRealtimData realtimedata);

    private:
        Ui::BoardSnapshot *ui;
        //QVBoxLayout* m_boardlistlay = new QVBoxLayout();
        QLayout* onewdtlay = Q_NULLPTR;
        QLayout* m_plotslay = Q_NULLPTR;
        QWidget* m_anotherwdt = Q_NULLPTR;

        QScrollArea* scrollarea = Q_NULLPTR;
        QStackedWidget* stackedwdt = Q_NULLPTR;

        //QLabel* mLabel;
        QMap<QString, QString> mBoardinfoQmap;

        std::vector<std::string> industry_board_vec;
        std::vector<std::string> concept_board_vec;


        QWidget* mPopup = Q_NULLPTR;
        QHBoxLayout *m_popuplay = Q_NULLPTR;
        QStackedWidget* m_popupstackedwdt = Q_NULLPTR;

        QMutex m_mutex;

    private slots:


};

#endif // BoardSnapshot_H
