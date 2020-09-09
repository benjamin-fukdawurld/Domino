#ifndef DOMINOPROBABILITYMANAGER_H
#define DOMINOPROBABILITYMANAGER_H

#include "engine/ai/DominoProbabilityMap.h"
#include "engine/Dominos.h"
#include "engine/Hand.h"

#include <vector>

class DominoProbabilityTensor
{
    protected:
        std::vector<DominoProbabilityMap> m_maps;
        uint8_t m_handSizes[4];

    public:
        DominoProbabilityTensor() = default;
        DominoProbabilityTensor(size_t nb_players);

        void setNumberOfPlayers(size_t nb_players);

        void clear() { m_maps.clear(); }
        DominoProbabilityMap &operator[](uint8_t playerIndex) { return m_maps[playerIndex]; }
        const DominoProbabilityMap &operator[](uint8_t playerIndex) const { return m_maps[playerIndex]; }

        bool isFound(const domino_t &d) const;

        size_t countRemainings(uint8_t playerIndex) const;
        size_t countRemainings() const;
        size_t countFound(uint8_t playerIndex) const;
        size_t countFound() const;

        size_t countUnfindable(uint8_t playerIndex) const;
        size_t countUnfindable() const;

        DominoProbabilityMap &operator[](size_t pos) { return m_maps[pos]; }

        void playerPlayed(uint8_t playerIndex, domino_t domino);

        void playerPassed(uint8_t playerIndex, const Dominos &dominos);

        void setHand(uint8_t playerIndex, const Hand &hand)
        {
            m_maps[playerIndex] = 0.0f;
            for(const domino_t &d : hand)
            {
                m_maps[playerIndex][d.first][d.second] = 1.0f;
                for(uint8_t i = 0; i < m_maps.size(); ++i)
                {
                    if(i == playerIndex)
                        continue;

                    m_maps[i][d.first][d.second] = 0.0f;
                }
            }

            for(uint8_t i = 1; i < m_maps.size(); ++i)
                m_maps[i] *= 7/21.0f;

            updateMaps();
        }

        std::string to_string() const;

    private:
        void updateMaps()
        {

            bool restart = false;
            do
            {
                restart = false;
                for(size_t j = 0; j < 7; ++j)
                {
                    for(size_t k = 0; k <= j; ++k)
                    {
                        bool is_found = isFound({j, k});
                        for(size_t i = 1; i < m_maps.size(); ++i)
                        {
                            if(m_maps[i][j][k] != 0.0f && m_maps[i][j][k] != 1.0f)
                            {
                                if(is_found)
                                    m_maps[i][j][k] = 0.0f;

                                m_maps[i][j][k] = static_cast<float>(
                                    (m_handSizes[i] - countFound(static_cast<uint8_t>(i))))
                                  / (28.0f - countUnfindable(static_cast<uint8_t>(i)));

                                if(m_maps[i][j][k] == 0.0f && m_maps[i][j][k] == 1.0f)
                                {
                                    restart = true;
                                    break;
                                }
                            }
                        }

                        if(restart)
                            break;
                    }
                    if(restart)
                        break;
                }
            } while(restart);
        }
};

#endif // DOMINOPROBABILITYMANAGER_H
