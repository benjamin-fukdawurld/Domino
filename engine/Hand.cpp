#include "engine/Hand.h"

#include <cassert>

std::vector<domino_move> Hand::getPlayable(const Dominos &dominos) const
{
    std::vector<domino_move> result;

    size_t i = 0;
    for(auto it = m_dominos.begin(); it != m_dominos.end(); ++it)
    {
        if(dominos.isPlaceableFront(*it))
            result.emplace_back(i, DominoInsertPosition::Head);
        if(dominos.isPlaceableBack(*it))
            result.emplace_back(i, DominoInsertPosition::Tail);

        ++i;
    }

    return result;
}

bool Hand::canPlay(const Dominos &dominos) const
{
    auto it = m_dominos.begin();
    while(!dominos.isPlaceable(*it) && it != m_dominos.end())
    {
        ++it;
    }

    return it != m_dominos.end();
}

void Hand::add(domino_t d)
{
    m_remainingDominos -= d;
    m_dominos.push_back(std::move(d));
}

domino_t Hand::remove(size_t index)
{
    assert(m_dominos.size() > index);
    auto it =m_dominos.begin();
    std::advance(it, index);
    domino_t result = *it;
    m_remainingDominos += result;
    m_dominos.erase(it);

    return result;
}

const domino_t &Hand::at(size_t index) const
{
    assert(m_dominos.size() > index);
    auto it = m_dominos.begin();
    std::advance(it, index);
    return *it;
}

domino_t &Hand::at(size_t index)
{
    assert(m_dominos.size() > index);
    auto it = m_dominos.begin();
    std::advance(it, index);
    return *it;
}
