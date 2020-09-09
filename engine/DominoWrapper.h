#ifndef DOMINOWRAPPER_H
#define DOMINOWRAPPER_H

#include <iostream>
#include <string>

#include "engine/Domino_types.h"
#include "Domino_functions.h"

class  ConstDominoWrapper
{
    protected:
        const domino_t &m_domino;

    public:
        ConstDominoWrapper(const domino_t &d): m_domino(d)
        {}

        const domino_t &domino() const { return m_domino; }

        uint8_t first() const { return m_domino.first; }

        uint8_t second() const { return m_domino.second; }

        bool isDouble() const { return domino_isDouble(m_domino); }

        uint8_t weight() const { return domino_weight(m_domino); }

        uint8_t attachPoint(const domino_t &d) const
        {
            return domino_attachPoint(m_domino, d);
        }

        bool canAttach(const domino_t &d) const
        {
            return domino_canAttach(m_domino, d);
        }

        std::ostream &print(std::ostream &out) const
        {
            return domino_print(m_domino, out);
        }

        std::string to_string() const
        {
            return domino_to_string(m_domino);
        }

        rapidjson::Value to_json(rapidjson::Document &doc) const
        {
            return domino_to_json(m_domino, doc);
        }
};

class  DominoWrapper
{
    protected:
        domino_t &m_domino;

    public:
        DominoWrapper(domino_t &d): m_domino(d)
        {}

        domino_t &domino() { return m_domino; }
        const domino_t &domino() const { return m_domino; }

        uint8_t first() const { return m_domino.first; }
        uint8_t &first() { return m_domino.first; }

        uint8_t second() const { return m_domino.second; }
        uint8_t &second() { return m_domino.second; }

        bool isDouble() const { return domino_isDouble(m_domino); }

        uint8_t weight() const { return domino_weight(m_domino); }

        uint8_t attachPoint(const domino_t &d) const
        {
            return domino_attachPoint(m_domino, d);
        }

        bool canAttach(const domino_t &d) const
        {
            return domino_canAttach(m_domino, d);
        }

        std::ostream &print(std::ostream &out) const
        {
            return domino_print(m_domino, out);
        }

        std::string to_string() const
        {
            return domino_to_string(m_domino);
        }

        rapidjson::Value to_json(rapidjson::Document &doc) const
        {
            return domino_to_json(m_domino, doc);
        }

        bool from_json(rapidjson::Value &val)
        {
            return domino_from_json(m_domino, val);
        }

        std::istream &scan(std::istream &in)
        {
            return domino_scan(m_domino, in);
        }

        void reverse() { domino_reverse(m_domino); }
};



#endif // DOMINOWRAPPER_H
