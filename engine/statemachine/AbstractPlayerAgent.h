#ifndef ABSTRACTPLAYERAGENT_H
#define ABSTRACTPLAYERAGENT_H

#include "engine/Hand.h"
#include "engine/Dominos.h"
#include "engine/Board.h"
#include <optional>

class IPlayerAgent
{
    public:
        IPlayerAgent() = default;
        virtual ~IPlayerAgent() = default;

        virtual uint8_t getPlayerIndex() const = 0;
        virtual void setPlayerIndex(uint8_t index) = 0;

        bool hasHand() const { return getHand() != nullptr; }
        virtual Hand *getHand() = 0;
        virtual const Hand *getHand() const = 0;
        virtual void setHand(Hand *hand) = 0;

        bool hasDominos() const { return getDominos() != nullptr; }
        virtual const Dominos *getDominos() const  = 0;
        virtual void setDominos(const Dominos *dominos) = 0;

        virtual std::optional<domino_move> play() = 0;
        virtual void onPlayerPass(uint8_t playerIndex) = 0;
        virtual void onPlayerPlayed(uint8_t playerIndex, domino_t domino) = 0;
        virtual void onPlayerWon(uint8_t index) = 0;
};


class AbstractPlayerAgent : public IPlayerAgent
{
    protected:
        Hand *m_hand;
        const Dominos *m_dominos;
        uint8_t m_playerIndex;

    public:
        AbstractPlayerAgent(uint8_t playerIndex, Hand *hand = nullptr, const Dominos *dominos = nullptr);
        ~AbstractPlayerAgent() override = default;

        uint8_t getPlayerIndex() const override;
        void setPlayerIndex(uint8_t index) override;

        Hand *getHand() override;
        const Hand *getHand() const override;
        virtual void setHand(Hand *hand) override;

        const Dominos *getDominos() const override;
        virtual void setDominos(const Dominos *dominos) override;
};

#endif // ABSTRACTPLAYERAGENT_H
