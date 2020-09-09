#include "engine/statemachine/GameStateMachine.h"


void GameStateMachineDef::menuAction(const to_menu_event &)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<GameStateMachineDef>&>(*this);
    agent->onMenu(fsm);
}

void GameStateMachineDef::configPartyAction(const to_config_party_event &)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<GameStateMachineDef>&>(*this);
    agent->onConfigParty(fsm);
}

void GameStateMachineDef::quitAction(const quit_event &)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<GameStateMachineDef>&>(*this);
    agent->onQuit(fsm);
}

void GameStateMachineDef::partyAction(const to_party_event &)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<GameStateMachineDef>&>(*this);
    agent->onParty(fsm);
}

void GameStateMachineDef::replayAction(const to_party_event &)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<GameStateMachineDef>&>(*this);
    Party &party = fsm.get_state<Party&>();
    party.process_event(ready_to_play_event());
    agent->onReplay(fsm);
}
