#include "engine/statemachine/GameAgent.h"


#include <iostream>

void GameAgent::onGameEntry(PartyStateMachine &party_state)
{
    party_state.agent = &partyAgent;
}

void GameAgent::onGameExit()
{

}

void GameAgent::onMenu(GSM &)
{
    //std::cout << "onMenu" << std::endl;
}

void GameAgent::onConfigParty(GSM &)
{
    //std::cout << "onConfigParty" << std::endl;
}

void GameAgent::onParty(GSM &)
{
    //std::cout << "onParty" << std::endl;
}

void GameAgent::onReplay(GSM &)
{
}

void GameAgent::onQuit(GSM &)
{
}

void GameAgent::onNoTransition(std::string_view evt_name, int state)
{
    std::cout << "here ! no transition from state " << state
              << " on event " << evt_name << std::endl;
}
