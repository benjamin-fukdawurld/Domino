#include "DominoProbabilityMap.h"

#include <sstream>

DominoProbabilityMap::DominoProbabilityMap()
{
    operator=(1.0f);
}

DominoProbabilityMap &DominoProbabilityMap::operator=(float f)
{
    for(size_t i = 0; i < 7; ++i)
        for(size_t j = 0; j < 7; ++j)
            m_map[i][j] = f;

    return *this;
}

DominoProbabilityMap &DominoProbabilityMap::operator&=(float f)
{
    for(size_t i = 0; i < 7; ++i)
        for(size_t j = 0; j < 7; ++j)
        {
            if(m_map[i][j] != 0.0f)
            m_map[i][j] = f;
        }

    return *this;
}

DominoProbabilityMap &DominoProbabilityMap::operator|=(float f)
{
    for(size_t i = 0; i < 7; ++i)
        for(size_t j = 0; j < 7; ++j)
        {
            if(m_map[i][j] == 0.0f)
            m_map[i][j] = f;
        }

    return *this;
}

DominoProbabilityMap &DominoProbabilityMap::operator*=(float f)
{
    for(size_t i = 0; i < 7; ++i)
        for(size_t j = 0; j < 7; ++j)
        {
            m_map[i][j] *= f;
        }

    return *this;
}

DominoProbabilityMap &DominoProbabilityMap::operator/=(float f)
{
    for(size_t i = 0; i < 7; ++i)
        for(size_t j = 0; j < 7; ++j)
        {
            m_map[i][j] /= f;
        }

    return *this;
}

DominoProbabilityMap &DominoProbabilityMap::operator&=(const DominoProbabilityMap &other)
{
    for(size_t i = 0; i < 7; ++i)
        for(size_t j = 0; j < 7; ++j)
        {
            if(m_map[i][j] == 1.0f && other[i][j] == 1.0f )
                m_map[i][j] = 1.0f;
            else
                m_map[i][j] = 0.0f;
        }

    return *this;
}

DominoProbabilityMap &DominoProbabilityMap::operator|=(const DominoProbabilityMap &other)
{
    for(size_t i = 0; i < 7; ++i)
        for(size_t j = 0; j < 7; ++j)
        {
            if(m_map[i][j] != 0.0f || other[i][j] != 0.0f )
                m_map[i][j] = 1.0f;
            else
                m_map[i][j] = 0.0f;
        }

    return *this;
}

std::string DominoProbabilityMap::to_string(float factor) const
{
    std::ostringstream oss;
    for(size_t i = 0; i < 7; ++i)
    {
        oss << "| ";
        for(size_t j = 0; j < 7; ++j)
            oss << m_map[i][j] * factor << " | ";

        oss << "\n";
    }

    return oss.str();
}

DominoProbabilityMapRow::DominoProbabilityMapRow(DominoProbabilityMap &map, size_t row) :
    m_map(map),
    m_row(row)
{

}

DominoProbabilityMapRow &DominoProbabilityMapRow::operator=(float f)
{
    for(size_t i = 0; i < 7; ++i)
    {
        m_map.m_map[m_row][i] = m_map.m_map[i][m_row] = f;
    }

    return *this;
}

DominoProbabilityMapCell DominoProbabilityMapRow::operator[](size_t column)
{
    return DominoProbabilityMapCell(m_map.m_map[m_row][column], m_map.m_map[column][m_row]);
}

float DominoProbabilityMapRow::operator[](size_t column) const { return m_map.m_map[m_row][column]; }

float DominoProbabilityMapRow::value() const
{
    float result = 0.0f;
    for(size_t i = 0; i < 7; ++i)
        result += m_map.m_map[m_row][i];

    return result;
}

ConstDominoProbabilityMapRow::ConstDominoProbabilityMapRow(const DominoProbabilityMap &map, size_t row) :
    m_map(map),
    m_row(row)
{

}

float ConstDominoProbabilityMapRow::operator[](size_t column) const { return m_map.m_map[m_row][column]; }

float ConstDominoProbabilityMapRow::value() const
{
    float result = 0.0f;
    for(size_t i = 0; i < 7; ++i)
        result += m_map.m_map[m_row][i];

    return result;
}


