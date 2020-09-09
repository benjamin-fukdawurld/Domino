#ifndef PARTYSTATEMACHINEEVENTS_H
#define PARTYSTATEMACHINEEVENTS_H

#include "engine/Hand.h"

struct ready_to_play_event {};

struct first_play_event
{
        Hand &playerHand;
        uint8_t playerIndex;
        first_play_event(uint8_t playerIndex, Hand &playerHand) :
            playerHand(playerHand),
            playerIndex(playerIndex)
        {}
};

struct pass_event
{
        Hand &playerHand;
        uint8_t playerIndex;
        pass_event(uint8_t playerIndex, Hand &playerHand) :
            playerHand(playerHand),
            playerIndex(playerIndex)
        {}
};

struct play_event
{
        Hand &playerHand;
        uint8_t playerIndex;
        play_event(uint8_t playerIndex, Hand &playerHand) :
            playerHand(playerHand),
            playerIndex(playerIndex)
        {}
};

struct reset_event
{
};

struct party_done_event {};

#endif // PARTYSTATEMACHINEEVENTS_H
