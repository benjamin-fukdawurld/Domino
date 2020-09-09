#include "engine/Board.h"

#include <random>

#include <sstream>
#include <cassert>

bool Board::isDone() const
{
    for(const auto &h: getPlayers())
    {
        if(h.size() == 0)
            return true;
    }

    for(const auto &h: getPlayers())
    {
        if(h.canPlay(getDominos()))
            return false;
    }

    return true;
}

uint8_t Board::getWinner() const
{
    for(uint8_t i = 0; i < m_players.size(); ++i)
    {
        if(m_players[i].size() == 0)
            return i;
    }

    uint8_t winner = 0;
    uint8_t weight = m_players[0].getWeight();
    for(uint8_t i = 1; i < m_players.size(); ++i)
    {
        if(weight > m_players[i].getWeight())
            winner = i;
    }

    return winner;
}

void Board::shuffleDominos()
{
    static std::random_device random_device;
    static std::default_random_engine random_engine/*(random_device())*/;
    m_dominos.shuffle(random_engine);
    m_dominos.shuffle(random_engine);
    m_savedDominos = m_dominos;
}

void Board::serve()
{
    for(size_t i = 0; i < m_players.size(); ++i)
    {
        for(size_t j = 0; j < 7; ++j)
            m_players[i].add(m_dominos.pop_front());
    }

    while(m_dominos.size() != 0)
        m_unused.add(m_dominos.pop_front());
}

void Board::playFirstDomino(size_t i, std::function<bool (domino_t)> func)
{
    auto it = std::find_if(m_players[i].begin(), m_players[i].end(), func);
    assert(it != m_players[i].end());

    size_t j = static_cast<size_t>(std::distance(m_players[i].begin(), it));
    m_dominos.push_front(m_players[i].remove(j));
}

std::string Board::to_string() const
{
    std::ostringstream oss;
    oss << m_dominos.to_string() << std::endl;
    for (size_t i = 0; i < m_players.size(); ++i)
    {
        oss << std::endl << "Player " << (i + 1) << ": " << m_players[i].to_string();
    }

    oss << std::endl << "unused :" << m_unused.to_string();

    return oss.str();
}

rapidjson::Value Board::to_json(rapidjson::Document &doc) const
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("dominos", 7), m_dominos.to_json(doc), doc.GetAllocator());
    rapidjson::Value playersArray(rapidjson::kArrayType);
    for(auto &h : m_players)
        playersArray.PushBack(h.to_json(doc), doc.GetAllocator());

    result.AddMember(rapidjson::Value("players", 7), playersArray, doc.GetAllocator());
    result.AddMember(rapidjson::Value("players", 7), m_unused.to_json(doc), doc.GetAllocator());
    return result;
}
