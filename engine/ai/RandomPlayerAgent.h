#ifndef RANDOMPLAYERAGENT_H
#define RANDOMPLAYERAGENT_H

#include "engine/statemachine/AbstractPlayerAgent.h"

class RandomPlayerAgent : public AbstractPlayerAgent
{
    public:
        using AbstractPlayerAgent::AbstractPlayerAgent;

        ~RandomPlayerAgent() override = default;

        std::optional<domino_move> play() override;

        void onPlayerPass(uint8_t playerIndex) override;

        void onPlayerPlayed(uint8_t playerIndex, domino_t domino) override;

        void onPlayerWon(uint8_t index) override;
};

#endif // RANDOMPLAYERAGENT_H
