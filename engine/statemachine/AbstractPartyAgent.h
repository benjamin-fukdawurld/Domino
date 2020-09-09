#ifndef ABSTRACTPARTYAGENT_H
#define ABSTRACTPARTYAGENT_H

#define BOOST_DISABLE_PRAGMA_MESSAGE
#include <boost/msm/back/state_machine.hpp>

#include <string_view>

#include "engine/statemachine/AbstractPlayerAgent.h"
#include "engine/Board.h"

namespace msm = boost::msm;

struct PartyDef;

struct AbstractPartyAgent
{
    typedef std::function<IPlayerAgent*(uint8_t, Board&)> PlayerGenerator;

    virtual ~AbstractPartyAgent();
    virtual void onPartyEntry() = 0;
    virtual void onPartyExit() = 0;

    virtual void pickFirstPlayer(msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onPass(uint8_t player_index, msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onFirstPlay(uint8_t, msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onPlay(uint8_t index, msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onPartyDone(uint8_t index, msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onReset(msm::back::state_machine<PartyDef> &) = 0;

    virtual void onInitEntry(uint8_t nb_player, msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onInitExit(msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onReadyToPlayEntry(msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onReadyToPlayExit(msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onPlayEntry(msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onPlayExit(msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onPartyDoneEntry(msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onPartyDoneExit(msm::back::state_machine<PartyDef> &fsm) = 0;
    virtual void onNoTransition(std::string_view evt_name, int state) = 0;
};

#endif // ABSTRACTPARTYAGENT_H
