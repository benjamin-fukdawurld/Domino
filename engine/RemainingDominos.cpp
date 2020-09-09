#include "RemainingDominos.h"

#include <cassert>

bool RemainingDominosProxy::operator[](uint8_t value) const
{
    uint8_t n = 1;
    n <<= value;
    return (m_remaining & n) != 0;
}

uint8_t RemainingDominosProxy::count() const
{
    uint8_t result = 0;
    for(uint8_t n = 0; n < 7; result += ((m_remaining >> n) & 1), ++n);

    return result;
}

RemainingDominosProxy RemainingDominosProxy::operator+=(uint8_t value)
{
    assert(value >= 0 && value <= 6);
    uint8_t n = 1;
    n <<=  value;
    m_remaining |= n;
    return *this;
}

RemainingDominosProxy RemainingDominosProxy::operator-=(uint8_t value)
{
    assert(value >= 0 && value <= 6);
    uint8_t n = 1;
    n <<=  value;
    m_remaining &= ~n;
    return *this;
}

RemainingDominosProxy RemainingDominos::operator[](uint8_t i)
{
    assert(i >= 0 && i <= 6);
    return m_remaining[i];
}

ConstRemainingDominosProxy RemainingDominos::operator[](uint8_t i) const
{
    assert(i >= 0 && i <= 6);
    return m_remaining[i];
}

RemainingDominos &RemainingDominos::operator+=(domino_t d)
{
    operator[](d.first) += d.second;
    operator[](d.second) += d.first;
    return *this;
}

RemainingDominos &RemainingDominos::operator-=(domino_t d)
{
    operator[](d.first) -= d.second;
    operator[](d.second) -= d.first;
    return *this;
}

RemainingDominos &RemainingDominos::operator&=(const RemainingDominos &other)
{
    for(uint8_t i = 0; i < 7; ++i)
        m_remaining[i] &= other.m_remaining[i];

    return *this;
}

RemainingDominos RemainingDominos::operator&(RemainingDominos other) const
{
    return other &= *this;
}

bool ConstRemainingDominosProxy::operator[](uint8_t value) const
{
    uint8_t n = 1;
    n <<= value;
    return (m_remaining & n) != 0;
}

uint8_t ConstRemainingDominosProxy::count() const
{
    uint8_t result = 0;
    for(uint8_t n = 0; n < 7; result += ((m_remaining >> n) & 1), ++n);

    return result;
}
