#ifndef UIGAMEAGENT_H
#define UIGAMEAGENT_H

#include <QObject>

#include "engine/statemachine/GameAgent.h"
#include "engine/statemachine/PartyAgent.h"
#include "engine/statemachine/GameStateMachine.h"
#include "gui/widget/GameCentralWidget.h"

class UiGameAgent : public QObject, public GameAgent
{
    Q_OBJECT
    protected:
        GameCentralWidget *m_centralWidget;

    public:
        UiGameAgent(GameCentralWidget *centralWidget, AbstractPartyAgent &partyAgent, QObject *parent = nullptr);

        void onMenu(GameStateMachine &) override
        {
            m_centralWidget->setMenuWidget();
        }

        void onConfigParty(GameStateMachine &) override
        {
            m_centralWidget->setConfigPartyWidget();
        }

        void onParty(GameStateMachine &) override
        {
            m_centralWidget->setPartyWidget();
        }
};

#endif // UIGAMEAGENT_H
