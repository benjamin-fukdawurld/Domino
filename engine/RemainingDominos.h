#ifndef REMAININGDOMINOS_H
#define REMAININGDOMINOS_H

#include "engine/Domino_types.h"

class RemainingDominosProxy;
class ConstRemainingDominosProxy;

class RemainingDominos
{
    private:
        uint8_t m_remaining[7];

    public:
        RemainingDominos() : m_remaining{0} {}

        RemainingDominosProxy operator[](uint8_t i);
        ConstRemainingDominosProxy operator[](uint8_t i) const;

        RemainingDominos &operator+=(domino_t d);
        RemainingDominos &operator-=(domino_t d);


        RemainingDominos &operator&=(const RemainingDominos &other);
        RemainingDominos operator&(RemainingDominos other) const;

        void clear()
        {
            for(uint8_t i = 0; i < 7; ++i)
                m_remaining[i] = 0;
        }

        void addAll()
        {
            for(uint8_t i = 0; i < 7; ++i)
                m_remaining[i] = 0b01111111;
        }
};

class ConstRemainingDominosProxy
{
    friend class RemainingDominos;
    private:
        const uint8_t &m_remaining;

    private:
        ConstRemainingDominosProxy(const uint8_t &remaining) : m_remaining(remaining) {}

    public:
        bool operator[](uint8_t value) const;

        uint8_t count() const;
};

class RemainingDominosProxy
{
    friend class RemainingDominos;
    private:
        uint8_t &m_remaining;

    private:
        RemainingDominosProxy(uint8_t &remaining) : m_remaining(remaining) {}

    public:
        bool operator[](uint8_t value) const;

        uint8_t count() const;

        RemainingDominosProxy operator+=(uint8_t value);

        RemainingDominosProxy operator-=(uint8_t value);
};

#endif // REMAININGDOMINOS_H
