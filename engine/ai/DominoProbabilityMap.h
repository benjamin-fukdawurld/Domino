#ifndef DOMINOPROBABILITYMAP_H
#define DOMINOPROBABILITYMAP_H

#include "engine/Domino_types.h"

#include <string>

class DominoProbabilityMap;

class DominoProbabilityMapCell
{
    protected:
        float &m_value1;
        float &m_value2;

    public:
        DominoProbabilityMapCell(float &value1, float &value2) : m_value1(value1), m_value2(value2)
        {}

        DominoProbabilityMapCell &operator=(float f) { m_value1 = m_value2 = f; return *this; }
        operator float() const { return m_value1; }
};

class DominoProbabilityMapRow
{
    protected:
        DominoProbabilityMap &m_map;
        size_t m_row;

    public:
        DominoProbabilityMapRow(DominoProbabilityMap &map, size_t row);

        DominoProbabilityMapRow &operator=(float f);

        DominoProbabilityMapCell operator[](size_t column);
        float operator[](size_t column) const;

        float value() const;
};

class ConstDominoProbabilityMapRow
{
    protected:
        const DominoProbabilityMap &m_map;
        size_t m_row;

    public:
        ConstDominoProbabilityMapRow(const DominoProbabilityMap &map, size_t row);

        float operator[](size_t column) const;

        float value() const;
};

class DominoProbabilityMap
{
    friend class DominoProbabilityMapRow;
    friend class ConstDominoProbabilityMapRow;

    protected:
        float m_map[7][7];
    public:
        DominoProbabilityMap();
        DominoProbabilityMap(DominoProbabilityMap &&) = default;
        DominoProbabilityMap(const DominoProbabilityMap &) = default;
        DominoProbabilityMap& operator=(DominoProbabilityMap &&) = default;
        DominoProbabilityMap& operator=(const DominoProbabilityMap &) = default;

        DominoProbabilityMap &operator=(float f);

        DominoProbabilityMap &operator&=(float f);
        DominoProbabilityMap &operator|=(float f);
        DominoProbabilityMap &operator*=(float f);
        DominoProbabilityMap &operator/=(float f);

        DominoProbabilityMap &operator&=(const DominoProbabilityMap &other);
        DominoProbabilityMap &operator|=(const DominoProbabilityMap &other);

        DominoProbabilityMapRow operator[](size_t row)
        {
            return DominoProbabilityMapRow(*this, row);
        }

        ConstDominoProbabilityMapRow operator[](size_t row) const
        {
            return ConstDominoProbabilityMapRow(*this, row);
        }

        std::string to_string(float factor = 1.0f) const;
};

#endif // DOMINOPROBABILITYMAP_H
