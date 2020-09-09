#include "engine/Dominos.h"

#include <algorithm>

#include <cassert>
#include <sstream>

Dominos::Dominos()
{
    reset();
}

void Dominos::reset()
{
    m_dominos.clear();
    for(uint8_t i = 0; i < 7; ++i)
    {
        for(uint8_t j = i; j < 7; ++j)
            m_dominos.push_back(std::make_pair(i, j));
    }

    m_remainingDominos.clear();
}

bool Dominos::push_front(domino_t d)
{
    if(m_dominos.empty() || d.second == head())
    {
        internal_push_front(std::move(d));
        return true;
    }

    if(d.first == head())
    {
        domino_reverse(d);
        internal_push_front(std::move(d));
        return true;
    }

    return false;
}

bool Dominos::push_back(domino_t d)
{
    if(m_dominos.empty() || d.first == tail())
    {
        internal_push_back(std::move(d));
        return true;
    }

    if(d.second == tail())
    {
        domino_reverse(d);
        internal_push_back(std::move(d));
        return true;
    }

    return false;
}

void Dominos::add(domino_t d)
{
    internal_push_back(d);
}

domino_t Dominos::pop_front()
{
    assert(!m_dominos.empty());
    domino_t result = front();
    m_dominos.erase(begin());
    m_remainingDominos += result;

    return result;
}

domino_t Dominos::pop_back()
{
    assert(!m_dominos.empty());
    domino_t result = back();
    auto it = begin();
    std::advance(it, size() - 1);
    m_dominos.erase(it);
    m_remainingDominos += result;

    return result;
}

domino_t Dominos::pop(size_t index)
{
    assert(m_dominos.size() > index);
    auto it = m_dominos.begin();
    std::advance(it, index);
    domino_t result = *it;
    m_remainingDominos += *it;
    m_dominos.erase(it);

    return result;
}

bool Dominos::isPlaceableFront(const domino_t & d) const
{
    return m_dominos.empty() || d.first == head() || d.second == head();
}

bool Dominos::isPlaceableBack(const domino_t &d) const
{
    return m_dominos.empty() || d.first == tail() || d.second == tail();
}

bool Dominos::isPlaceable(domino_t d) const
{
    if(m_dominos.empty())
        return true;

    return d.first == head() || d.first == tail()
            || d.second == head() || d.second == tail();
}

void Dominos::internal_push_front(domino_t d)
{
    m_dominos.push_front(d);
    m_remainingDominos -= d;
}

void Dominos::internal_push_back(domino_t d)
{
    m_dominos.push_back(d);
    m_remainingDominos -= d;
}

void Dominos::updateRemaining()
{
    m_remainingDominos.addAll();

    for(const domino_t &d: m_dominos)
        m_remainingDominos -= d;
}
