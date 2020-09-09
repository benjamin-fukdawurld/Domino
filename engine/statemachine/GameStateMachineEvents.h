#ifndef GAMESTATEMACHINEEVENTS_H
#define GAMESTATEMACHINEEVENTS_H

#include <cstdint>

struct quit_event {};
struct to_config_party_event {};
struct to_party_event
{
        uint8_t numberOfPlayers;
        to_party_event(uint8_t numberOfPlayers) : numberOfPlayers(numberOfPlayers) {}
};
struct to_menu_event {};

struct init_party_event
{
        uint8_t numberOfPlayers;
        init_party_event(uint8_t numberOfPlayers) : numberOfPlayers(numberOfPlayers) {}
};

struct reset_party_event
{};

#endif // GAMESTATEMACHINEEVENTS_H
