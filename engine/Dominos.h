#ifndef DOMINOS_H
#define DOMINOS_H

#include "DominoWrapper.h"
#include "RemainingDominos.h"

class Dominos
{
    public:
        typedef domino_t value_type;
        typedef domino_t* pointer;
        typedef const domino_t* const_pointer;
        typedef domino_t& reference;
        typedef const domino_t&	const_reference;
        typedef domino_deque::iterator iterator;
        typedef domino_deque::const_iterator		const_iterator;
        typedef domino_deque::const_reverse_iterator	const_reverse_iterator;
        typedef domino_deque::reverse_iterator reverse_iterator;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
        typedef domino_deque::allocator_type allocator_type;

    protected:
        domino_deque m_dominos;
        RemainingDominos m_remainingDominos;

    public:
        Dominos();

        void reset();

        template<typename RandomEngine>
        void shuffle(RandomEngine random_engine) { domino_deque_shuffle(m_dominos, random_engine);}

        uint8_t head() const { return m_dominos.front().first; }
        uint8_t tail() const { return m_dominos.back().second; }

        domino_t &front() { return m_dominos.front(); }
        const domino_t &front() const { return m_dominos.front(); }

        domino_t &back() { return m_dominos.back(); }
        const domino_t &back() const { return m_dominos.back(); }

        bool push_front(domino_t d);

        bool push_back(domino_t d);

        void add(domino_t d);

        domino_t pop_front();

        domino_t pop_back();

        domino_t pop(size_t index);

        domino_t &at(size_t index) { return m_dominos[index]; }

        const domino_t at(size_t index) const { return m_dominos[index]; }

        std::ostream &print(std::ostream &out) const
        {
            return domino_deque_print(m_dominos, out);
        }

        std::string to_string() const
        {
            return domino_deque_to_string(m_dominos);
        }

        rapidjson::Value to_json(rapidjson::Document &doc) const
        {
            return domino_deque_to_json(m_dominos, doc);
        }

        bool from_json(const rapidjson::Value &val)
        {
            return domino_deque_from_json(m_dominos, val);
        }

        size_t hash() const
        {
            return std::hash<std::string>()(domino_deque_to_string(m_dominos));
        }

        std::istream &scan(std::istream &in)
        {
            return domino_deque_scan(m_dominos, in);
        }

        bool isPlaceableFront(const domino_t &d) const;
        bool isPlaceableBack(const domino_t &d) const;

        bool isPlaceable(domino_t d) const;

        RemainingDominos &getRemaining() { return m_remainingDominos; }
        const RemainingDominos &getRemaining() const { return m_remainingDominos; }

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

        ConstDominoWrapper operator[](size_t index) const { return m_dominos[index]; }
        DominoWrapper operator[](size_t index) { return m_dominos[index]; }


    protected:
        void internal_push_front(domino_t d);
        void internal_push_back(domino_t d);

        void updateRemaining();
};

namespace std
{
    template<>
    struct hash<Dominos>
    {
        size_t operator()(const Dominos &d) const
        {
            return d.hash();
        }
    };

    template<>
    struct less<Dominos>
    {
        bool operator()(const Dominos &a, const Dominos &b)
        {
            std::hash<Dominos> h;
            return h(a) < h(b);
        }
    };

    template<>
    struct equal_to<Dominos>
    {
        bool operator()(const Dominos &a, const Dominos &b)
        {
            std::hash<Dominos> h;
            return h(a) == h(b);
        }
    };
}

#endif // DOMINOS_H
