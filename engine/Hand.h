#ifndef HAND_H
#define HAND_H

#include "engine/Domino_types.h"
#include "Domino_functions.h"
#include "RemainingDominos.h"
#include "engine/Dominos.h"
#include <list>

class Hand
{
    public:
        typedef domino_t value_type;
        typedef domino_t* pointer;
        typedef const domino_t* const_pointer;
        typedef domino_t& reference;
        typedef const domino_t&	const_reference;
        typedef domino_list::iterator iterator;
        typedef domino_list::const_iterator		const_iterator;
        typedef domino_list::const_reverse_iterator	const_reverse_iterator;
        typedef domino_list::reverse_iterator reverse_iterator;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef domino_list::allocator_type allocator_type;

    protected:
        domino_list m_dominos;
        RemainingDominos m_remainingDominos;

    public:
        Hand() { clear(); }

        uint8_t getWeight() const
        {
            uint8_t result = 0;
            for(auto &d: m_dominos)
                result += domino_weight(d);

            return result;
        }

        void clear() { m_dominos.clear(); m_remainingDominos.addAll(); }

        std::vector<domino_move> getPlayable(const Dominos &dominos) const;
        bool canPlay(const Dominos &dominos) const;

        void add(domino_t d);

        domino_t remove(size_t index);
        const RemainingDominos &getRemainingDominos() const { return m_remainingDominos; }
        uint8_t count(uint8_t i) { return 7 - m_remainingDominos[i].count(); }

        const domino_t &at(size_t index) const;
        domino_t &at(size_t index);

        size_t size() const { return m_dominos.size(); }

        iterator begin() { return  m_dominos.begin(); }
        const_iterator begin() const { return  m_dominos.begin(); }
        const_iterator cbegin() const { return  m_dominos.cbegin(); }

        iterator end() { return  m_dominos.end(); }
        const_iterator end() const { return  m_dominos.end(); }
        const_iterator cend() const { return  m_dominos.cend(); }

        reverse_iterator rbegin() { return  m_dominos.rbegin(); }
        const_reverse_iterator rbegin() const { return  m_dominos.rbegin(); }
        const_reverse_iterator crbegin() const { return  m_dominos.crbegin(); }

        reverse_iterator rend() { return  m_dominos.rend(); }
        const_reverse_iterator rend() const { return  m_dominos.rend(); }
        const_reverse_iterator crcend() const { return  m_dominos.crend(); }

        domino_t &front() { return m_dominos.front(); }
        const domino_t &front() const { return m_dominos.front(); }

        domino_t &back() { return m_dominos.back(); }
        const domino_t &back() const { return m_dominos.back(); }

        ConstDominoWrapper operator[](uint8_t i) const { return ConstDominoWrapper(at(i));}
        DominoWrapper operator[](uint8_t i) { return DominoWrapper(at(i));}


        std::ostream &print(std::ostream &out) const
        {
            return domino_list_print(m_dominos, out);
        }

        std::string to_string() const
        {
            return domino_list_to_string(m_dominos);
        }

        rapidjson::Value to_json(rapidjson::Document &doc) const
        {
            return domino_list_to_json(m_dominos, doc);
        }

        bool from_json(const rapidjson::Value &val)
        {
            return domino_list_from_json(m_dominos, val);
        }

        size_t hash() const
        {
            return std::hash<std::string>()(domino_list_to_string(m_dominos));
        }

        std::istream &scan(std::istream &in)
        {
            return domino_list_scan(m_dominos, in);
        }
};

namespace std
{
    template<>
    struct hash<Hand>
    {
        size_t operator()(const Hand &d) const
        {
            return d.hash();
        }
    };

    template<>
    struct less<Hand>
    {
        bool operator()(const Hand &a, const Hand &b)
        {
            std::hash<Hand> h;
            return h(a) < h(b);
        }
    };

    template<>
    struct equal_to<Hand>
    {
        bool operator()(const Hand &a, const Hand &b)
        {
            std::hash<Hand> h;
            return h(a) == h(b);
        }
    };
}

#endif // HAND_H
