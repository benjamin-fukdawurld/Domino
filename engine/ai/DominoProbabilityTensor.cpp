#include "DominoProbabilityTensor.h"

#include <sstream>

DominoProbabilityTensor::DominoProbabilityTensor(size_t nb_players) :
    m_maps(nb_players)
{}

void DominoProbabilityTensor::setNumberOfPlayers(size_t nb_players)
{
    clear();
    m_maps.resize(nb_players);
    for(size_t i = 0; i < nb_players; ++i)
        m_handSizes[i] = 7;
}

bool DominoProbabilityTensor::isFound(const domino_t &d) const
{
    for(auto &m : m_maps)
    {
        if(m[d.first][d.second] == 1.0f)
            return true;
    }

    return false;
}

size_t DominoProbabilityTensor::countRemainings(uint8_t playerIndex) const
{
    size_t result = 0;
    const DominoProbabilityMap &m = m_maps[playerIndex];
    for(size_t i = 0; i < 7; ++i)
    {
        for(size_t j = 0; j <= i; ++j)
            result += (m[i][j] != 1.0f ? 1 : 0);
    }

    return result;
}

size_t DominoProbabilityTensor::countFound() const
{
    size_t result = 0;
    DominoProbabilityMap m;
    m = 0.0f;
    for(size_t i = 0; i < m_maps.size(); ++i)
        result += countFound(static_cast<uint8_t>(i));

    return result;
}

size_t DominoProbabilityTensor::countUnfindable(uint8_t playerIndex) const
{
    size_t result = 0;
    for(size_t i = 0; i < 7; ++i)
    {
        for(size_t j = 0; j <= i; ++j)
            result += (m_maps[playerIndex][i][j] == 0.0f ? 1 : 0);
    }

    return result;
}

size_t DominoProbabilityTensor::countUnfindable() const
{
    size_t result = 0;
    DominoProbabilityMap m;
    m = 0.0f;
    for(auto &map : m_maps)
        m |= map;

    for(size_t i = 0; i < 7; ++i)
    {
        for(size_t j = 0; j <= i; ++j)
        result += (m[i][j] == 0.0f ? 1 : 0);
    }

    return result;
}

void DominoProbabilityTensor::playerPlayed(uint8_t playerIndex, domino_t domino)
{
    for(size_t i = 0; i < m_maps.size(); ++ i)
        m_maps[i][domino.first][domino.second] = 0.0f;

    --m_handSizes[playerIndex];
    updateMaps();
}

void DominoProbabilityTensor::playerPassed(uint8_t playerIndex, const Dominos &dominos)
{
    m_maps[playerIndex][dominos.head()] = 0.0f;
    m_maps[playerIndex][dominos.tail()] = 0.0f;
    updateMaps();
}

size_t DominoProbabilityTensor::countRemainings() const
{
    size_t result = 0;
    DominoProbabilityMap m;
    m = 0.0f;
    for(auto &map : m_maps)
        m |= map;

    for(size_t i = 0; i < 7; ++i)
    {
        for(size_t j = 0; j <= i; ++j)
            result += (m[i][j] == 0.0f ? 1 : 0);
    }

    return result;
}

size_t DominoProbabilityTensor::countFound(uint8_t playerIndex) const
{
    size_t result = 0;

    for(size_t i = 0; i < 7; ++i)
    {
        for(size_t j = 0; j <= i; ++j)
        result += (m_maps[playerIndex][i][j] == 1.0f ? 1 : 0);
    }

    return result;
}

std::string DominoProbabilityTensor::to_string() const
{
    std::ostringstream oss;
    oss << "Player 0:\n" << m_maps[0].to_string();
    for(uint8_t i = 1; i < m_maps.size(); ++i)
        oss << "Player " << static_cast<int>(i) << ":\n" << m_maps[i].to_string() << std::endl;

    return oss.str();
}
