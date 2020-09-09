#ifndef ABSTRACTGAMEAGENT_H
#define ABSTRACTGAMEAGENT_H

#include "engine/statemachine/AbstractPartyAgent.h"

#include "engine/statemachine/PartyStateMachine.h"

struct GameStateMachineDef;

struct AbstractGameAgent
{
    typedef msm::back::state_machine<GameStateMachineDef> GSM;

    AbstractPartyAgent &partyAgent;

    AbstractGameAgent(AbstractPartyAgent &partyAgent);
    virtual ~AbstractGameAgent();


    virtual void onGameEntry(PartyStateMachine&) = 0;
    virtual void onGameExit() = 0;

    virtual void onMenu(GSM &gsm) = 0;
    virtual void onConfigParty(GSM &gsm) = 0;
    virtual void onParty(GSM &gsm) = 0;
    virtual void onReplay(GSM &gsm) = 0;
    virtual void onQuit(GSM &gsm) = 0;
    virtual void onNoTransition(std::string_view evt_name, int state) = 0;
};


#endif // ABSTRACTGAMEAGENT_H
