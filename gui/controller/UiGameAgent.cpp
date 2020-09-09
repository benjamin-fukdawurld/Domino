#include "gui/controller/UiGameAgent.h"

UiGameAgent::UiGameAgent(GameCentralWidget *centralWidget, AbstractPartyAgent &partyAgent, QObject *parent):
    QObject (parent),
    GameAgent(partyAgent),
    m_centralWidget(centralWidget)
{}
