#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gui/widget/GameCentralWidget.h"
#include "gui/widget/GameMenuWidget.h"
#include "gui/widget/ConfigPartyWidget.h"
#include "gui/widget/PartyWidget.h"
#include "gui/controller/UiGameAgent.h"
#include "gui/controller/UiPartyAgent.h"
#include "gui/controller/GameController.h"
#include "gui/controller/PartyController.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    protected:
        GameMenuWidget *m_menuWidget;
        ConfigPartyWidget *m_configWidget;
        PartyWidget *m_partyWidget;
        GameCentralWidget *m_centralWidget;
        UiPartyAgent m_partyAgent;
        UiGameAgent m_gameAgent;

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;

    public slots:
        void onReplay(uint8_t nb_players);
};

#endif // MAINWINDOW_H
