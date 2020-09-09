#include "WeightPlayerAgent.h"

std::optional<domino_move > weight_play_helper(const Hand *hand, const Dominos *dominos)
{
    auto playables = hand->getPlayable(*dominos);
    if(playables.empty())
        return std::nullopt;

    if(playables.size() > 1)
    {
        return *std::max_element(playables.begin(), playables.end(), [hand](domino_move a, domino_move b){
            return domino_weight(hand->at(a.first)) < domino_weight(hand->at(b.first));
        });
    }

    return playables.front();
}

WeightPlayerAgentDecorator::~WeightPlayerAgentDecorator()
{

}
