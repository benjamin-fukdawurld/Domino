#ifndef DOUBLEPLAYERAGENT_H
#define DOUBLEPLAYERAGENT_H

#include "engine/ai/WeightPlayerAgent.h"

#include "engine/DominoWrapper.h"

std::optional<domino_move> double_play_helper(const Hand *hand, const Dominos *dominos);

template <typename ParentAgent>
class MetaDoublePlayerAgentDecorator : public ParentAgent
{
    public:
        using ParentAgent::ParentAgent;
        ~MetaDoublePlayerAgentDecorator() override = default;


        std::optional<domino_move> play() override
        {
            std::optional<domino_move> result = double_play_helper(ParentAgent::getHand(), ParentAgent::getDominos());
            if(result.has_value())
                return result;

            return ParentAgent::play();
        }
};

template<>
class MetaDoublePlayerAgentDecorator<AbstractPlayerAgent> : public RandomPlayerAgent
{
    public:
        using RandomPlayerAgent::RandomPlayerAgent;
        ~MetaDoublePlayerAgentDecorator() override = default;


        std::optional<domino_move> play() override
        {
            std::optional<domino_move> result = double_play_helper(getHand(), getDominos());
            if(result.has_value())
                return result;

            return RandomPlayerAgent::play();
        }
};

class DoublePlayerAgentDecorator : public IPlayerAgent
{
    protected:
        IPlayerAgent *m_agent;

    public:
        DoublePlayerAgentDecorator(IPlayerAgent *agent = nullptr) : IPlayerAgent(), m_agent(agent)
        {}
        ~DoublePlayerAgentDecorator() override;
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
            std::optional<domino_move> result = double_play_helper(getHand(), getDominos());
            if(result.has_value())
                return result;

            return m_agent->play();
        }


        void onPlayerPass(uint8_t playerIndex) override { m_agent->onPlayerPass(playerIndex); }

        void onPlayerPlayed(uint8_t playerIndex, domino_t domino) override
        {
            m_agent->onPlayerPlayed(playerIndex, domino);
        }

        void onPlayerWon(uint8_t index) override { m_agent->onPlayerWon(index); }
};

typedef MetaDoublePlayerAgentDecorator<AbstractPlayerAgent> DoublePlayerAgent;
typedef MetaDoublePlayerAgentDecorator<WeightPlayerAgent> DoubleWeightPlayerAgent;

#endif // DOUBLEPLAYERAGENT_H
