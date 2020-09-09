#ifndef GAMECENTRALWIDGET_H
#define GAMECENTRALWIDGET_H

#include <QStackedWidget>

#include "gui/widget/GameMenuWidget.h"
#include "gui/widget/ConfigPartyWidget.h"
#include "gui/widget/PartyWidget.h"

class GameCentralWidget : public QStackedWidget
{
    Q_OBJECT
    public:
        enum class Widget : int
        {
            Menu = 0,
            ConfigParty = 1,
            Party = 2
        };

    public:
        GameCentralWidget(GameMenuWidget *menu, ConfigPartyWidget *config, PartyWidget *party,
                          QWidget *parent = nullptr);

        ~GameCentralWidget() override;

        QWidget *getWidget(Widget widget);

        GameMenuWidget *getMenuWidget();

        ConfigPartyWidget *getConfigPartyWidget();

        PartyWidget *getPartyWidget();

    public slots:
        void setVisibleWidget(Widget widget);

        void setMenuWidget();
        void setConfigPartyWidget();
        void setPartyWidget();
};

#endif // GAMECENTRALWIDGET_H
