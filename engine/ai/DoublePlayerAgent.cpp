#include "DoublePlayerAgent.h"

std::optional<domino_move> double_play_helper(const Hand *hand, const Dominos *dominos)
{
    std::vector<domino_move> playables = hand->getPlayable(*dominos);
    std::vector<domino_move> doubles;
    for(auto m : playables)
    {
        if(domino_isDouble(hand->at(m.first)))
            doubles.push_back(m);
    }

    if(doubles.empty())
        return std::nullopt;

    return *std::max_element(doubles.begin(), doubles.end(), [hand](domino_move a, domino_move b) {
            return domino_weight(hand->at(a.first)) < domino_weight(hand->at(b.first));
     });
}
