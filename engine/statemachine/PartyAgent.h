#ifndef PARTYAGENT_H
#define PARTYAGENT_H

#include "engine/statemachine/AbstractPartyAgent.h"

#include "engine/statemachine/AbstractPlayerAgent.h"

namespace msm = boost::msm;

struct PartyAgent : public AbstractPartyAgent
{
    PlayerGenerator playerGenerator;
    std::vector<std::unique_ptr<IPlayerAgent>> players;

    PartyAgent(PlayerGenerator playerGenerator);
    ~PartyAgent() override = default;
    void onPartyEntry() override;
    void onPartyExit() override;

    void pickFirstPlayer(msm::back::state_machine<PartyDef> &fsm) override;
    void onPass(uint8_t player_index, msm::back::state_machine<PartyDef> &fsm) override;
    void onFirstPlay(uint8_t, msm::back::state_machine<PartyDef> &fsm) override;
    void onPlay(uint8_t index, msm::back::state_machine<PartyDef> &fsm) override;
    void onPartyDone(uint8_t index, msm::back::state_machine<PartyDef> &) override;
    void onReset(msm::back::state_machine<PartyDef> &fsm) override;

    void onInitEntry(uint8_t nb_player, msm::back::state_machine<PartyDef> &fsm) override;
    void onInitExit(msm::back::state_machine<PartyDef> &fsm) override;
    void onReadyToPlayEntry(msm::back::state_machine<PartyDef> &fsm) override;
    void onReadyToPlayExit(msm::back::state_machine<PartyDef> &fsm) override;
    void onPlayEntry(msm::back::state_machine<PartyDef> &fsm) override;
    void onPlayExit(msm::back::state_machine<PartyDef> &fsm) override;
    void onPartyDoneEntry(msm::back::state_machine<PartyDef> &fsm) override;
    void onPartyDoneExit(msm::back::state_machine<PartyDef> &fsm) override;
    void onNoTransition(std::string_view evt_name, int state) override;
};

#endif // PARTYAGENT_H
