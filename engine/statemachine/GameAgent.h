#ifndef GAMEAGENT_H
#define GAMEAGENT_H

#include "engine/statemachine/AbstractGameAgent.h"

struct GameAgent : public AbstractGameAgent
{
    using AbstractGameAgent::AbstractGameAgent;

    ~GameAgent() override = default;

    void onGameEntry(PartyStateMachine &party_state) override;
    void onGameExit() override;

    void onMenu(GSM &gsm) override;
    void onConfigParty(GSM &gsm) override;
    void onParty(GSM &gsm) override;
    void onReplay(GSM &gsm) override;
    void onQuit(GSM &gsm) override;
    void onNoTransition(std::string_view evt_name, int state) override;
};

#endif // GAMEAGENT_H
