#include "engine/statemachine/PartyStateMachine.h"

void PartyDef::readyToPlayAction(const ready_to_play_event &)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<PartyDef>&>(*this);
    agent->pickFirstPlayer(fsm);
}

void PartyDef::readyToPlayAction(const reset_event &)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<PartyDef>&>(*this);
    agent->onReset(fsm);
    agent->pickFirstPlayer(fsm);
}

void PartyDef::playAction(const first_play_event &evt)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<PartyDef>&>(*this);
    agent->onFirstPlay(evt.playerIndex, fsm);
}

bool PartyDef::playGuard(const play_event &)
{
    //std::cout << __func__ << std::endl;
    for(const auto &h: board.getPlayers())
    {
        if(h.size() > 0 || h.canPlay(board.getDominos()))
            return false;
    }

    return true;
}

void PartyDef::playAction(const play_event &evt)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<PartyDef>&>(*this);
    agent->onPlay(evt.playerIndex, fsm);
}

void PartyDef::playAction(const pass_event &evt)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<PartyDef>&>(*this);
    agent->onPass(evt.playerIndex, fsm);
}

bool PartyDef::partyDoneGuard(const play_event &)
{
    //std::cout << __func__ << std::endl;
    return board.isDone();
}

bool PartyDef::partyNotDoneGuard(const play_event &)
{
    //std::cout << __func__ << std::endl;
    return !board.isDone();
}

void PartyDef::partyDoneAction(const play_event &)
{
    //std::cout << __func__ << std::endl;
    auto &fsm = static_cast<msm::back::state_machine<PartyDef>&>(*this);
    agent->onPartyDone(static_cast<uint8_t>(fsm.board.getWinner()), fsm);
}
