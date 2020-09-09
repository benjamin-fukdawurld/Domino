#ifndef BOARD_H
#define BOARD_H

#include "engine/Dominos.h"
#include "engine/Hand.h"

class Board
{
    protected:
        Dominos m_dominos;
        Dominos m_savedDominos;
        std::vector<Hand> m_players;
        Hand m_unused;

    public:
        Board()
        {
            m_players.reserve(4);
        }

        void clear()
        {
            m_dominos.reset();
            m_players.clear();
            m_unused.clear();
        }

        void reset()
        {
            m_dominos = m_savedDominos;
            for(auto &h: m_players)
                h.clear();

            m_unused.clear();
        }

        bool isDone() const;

        uint8_t getWinner() const;

        Dominos &getDominos() { return m_dominos; }
        const Dominos &getDominos() const { return m_dominos; }

        std::vector<Hand> &getPlayers() { return m_players; }
        const std::vector<Hand> &getPlayers() const { return m_players; }

        Hand &getPlayer(size_t index) { return m_players[index]; }
        const Hand &getPlayer(size_t index) const { return m_players[index]; }

        size_t getNumberOfPlayers() const { return m_players.size(); }

        Hand &getUnused() { return m_unused; }
        const Hand &getUnused() const { return m_unused; }

        void setNumberOfPlayers(size_t n) { m_players.resize(n); }
        void shuffleDominos();
        void serve();

        size_t pickFirstPlayer(std::function<size_t(std::vector<Hand> &)> func);

        void playFirstDomino(size_t i, std::function<bool(domino_t)> func);

        std::string to_string() const;

        rapidjson::Value to_json(rapidjson::Document &doc) const;

        bool from_json(rapidjson::Value &val);
};

#endif // BOARD_H
