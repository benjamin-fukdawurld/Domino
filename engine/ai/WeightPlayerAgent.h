#ifndef WEIGHTPLAYERAGENT_H
#define WEIGHTPLAYERAGENT_H

#include "engine/ai/RandomPlayerAgent.h"

#include "engine/DominoWrapper.h"

std::optional<domino_move> weight_play_helper(const Hand *hand, const Dominos *dominos);

template <typename ParentAgent>
class MetaWeightPlayerAgentDecorator : public ParentAgent
{
    public:
        using ParentAgent::ParentAgent;
        ~MetaWeightPlayerAgentDecorator() override = default;


        std::optional<domino_move> play() override
        {
            return weight_play_helper(ParentAgent::getHand(), ParentAgent::getDominos());
        }
};

template<>
class MetaWeightPlayerAgentDecorator<AbstractPlayerAgent> : public AbstractPlayerAgent
{
    public:
        using AbstractPlayerAgent::AbstractPlayerAgent;
        ~MetaWeightPlayerAgentDecorator() override = default;


        std::optional<domino_move> play() override
        {
            return weight_play_helper(getHand(), getDominos());
        }


        void onPlayerPass(uint8_t) override {}

        void onPlayerPlayed(uint8_t, domino_t) override {}

        void onPlayerWon(uint8_t) override {}
};

class WeightPlayerAgentDecorator : public IPlayerAgent
{
    protected:
        IPlayerAgent *m_agent;

    public:
        WeightPlayerAgentDecorator(IPlayerAgent *agent = nullptr) : IPlayerAgent(), m_agent(agent)
        {}
        ~WeightPlayerAgentDecorator() override;


        IPlayerAgent *getAgent() { return m_agent; }
        const IPlayerAgent *getAgent() const { return m_agent; }
        void setAgent(IPlayerAgent *agent) { m_agent = agent; }

        uint8_t getPlayerIndex() const override { return m_agent->getPlayerIndex(); }
        void setPlayerIndex(uint8_t index) override { m_agent->setPlayerIndex(index); }
        Hand *getHand() override { return m_agent->getHand(); }
        const Hand *getHand() const override { return m_agent->getHand(); }
        virtual void setHand(Hand *hand) override { m_agent->setHand(hand); }

        const Dominos *getDominos() const override { return m_agent->getDominos(); }
        virtual void setDominos(const Dominos *dominos) override { return m_agent->setDominos(dominos); }

        std::optional<domino_move> play() override
        {
            return weight_play_helper(getHand(), getDominos());
        }


        void onPlayerPass(uint8_t playerIndex) override { m_agent->onPlayerPass(playerIndex); }

        void onPlayerPlayed(uint8_t playerIndex, domino_t domino) override
        {
            m_agent->onPlayerPlayed(playerIndex, domino);
        }

        void onPlayerWon(uint8_t index) override { m_agent->onPlayerWon(index); }
};

typedef MetaWeightPlayerAgentDecorator<AbstractPlayerAgent> WeightPlayerAgent;

#endif // WEIGHTPLAYERAGENT_H
