#include "RandomPlayerAgent.h"

#include <cassert>

std::optional<domino_move> RandomPlayerAgent::play()
{
    assert(hasHand() && hasDominos());

    auto playable = getHand()->getPlayable(*getDominos());
    if(playable.empty())
        return std::nullopt;

    return playable[static_cast<size_t>(std::abs(std::rand())) % playable.size()];
}

void RandomPlayerAgent::onPlayerPass(uint8_t) {}

void RandomPlayerAgent::onPlayerPlayed(uint8_t, domino_t) {}

void RandomPlayerAgent::onPlayerWon(uint8_t) {}
