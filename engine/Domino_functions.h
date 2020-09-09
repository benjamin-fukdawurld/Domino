#ifndef DOMINO_FUNCTIONS_H
#define DOMINO_FUNCTIONS_H

#include "engine/Domino_types.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <rapidjson/document.h>

inline bool domino_isDouble(const domino_t &domino) { return domino.first == domino.second; }

inline uint8_t domino_weight(const domino_t &domino) { return domino.first + domino.second; }

uint8_t domino_attachPoint(const domino_t &d1, const domino_t &d2);

bool domino_canAttach(const domino_t &d1, const domino_t &d2);

std::ostream &domino_print(const domino_t &d, std::ostream &out);

std::istream &domino_scan(domino_t &d, std::istream &in);

std::string domino_to_string(const domino_t &domino);

rapidjson::Value domino_to_json(const domino_t &domino, rapidjson::Document &doc);

bool domino_from_json(domino_t &domino, const rapidjson::Value &doc);

void domino_reverse(domino_t &domino);

size_t domino_id(domino_t domino);

std::ostream &operator<<(std::ostream &out, const domino_t &domino);

std::istream &operator>>(std::istream &in, domino_t &domino);

template<typename RandomEngine>
void domino_deque_shuffle(domino_deque &dominos, RandomEngine random_engine)
{
    std::shuffle(dominos.begin(), dominos.end(), random_engine);
}

std::ostream &domino_deque_print(const domino_deque &dominos, std::ostream &out);

std::istream &domino_deque_scan(domino_deque &dominos, std::istream &in);

std::string domino_deque_to_string(const domino_deque &domino);

rapidjson::Value domino_deque_to_json(const domino_deque &domino, rapidjson::Document &doc);

bool domino_deque_from_json(domino_deque &domino, const rapidjson::Value &val);

std::ostream &operator<<(std::ostream &out, const domino_deque &dominos);

std::istream &operator>>(std::istream &in, domino_deque &dominos);

std::ostream &domino_list_print(const domino_list &dominos, std::ostream &out);

std::istream &domino_list_scan(domino_list &dominos, std::istream &in);

std::string domino_list_to_string(const domino_list &domino);

rapidjson::Value domino_list_to_json(const domino_list &domino, rapidjson::Document &doc);

bool domino_list_from_json(domino_list &domino, const rapidjson::Value &val);

std::ostream &operator<<(std::ostream &out, const domino_list &dominos);

std::istream &operator>>(std::istream &in, domino_list &dominos);

std::string DominoInsertPosition_to_string(DominoInsertPosition pos);

DominoInsertPosition DominoInsertPosition_from_string(std::string_view pos);

rapidjson::Value DominoInsertPosition_to_json(DominoInsertPosition pos, rapidjson::Document &doc);

bool DominoInsertPosition_from_json(DominoInsertPosition &pos, const rapidjson::Value &val);

std::string domino_move_to_string(const domino_move &move);

rapidjson::Value domino_move_to_json(const domino_move &move, rapidjson::Document &doc);

bool domino_move_from_json(domino_move &move, const rapidjson::Value &val);

namespace std
{
    template<>
    struct hash<domino_t>
    {
        size_t operator()(const domino_t &d) const
        {
            return std::hash<std::string>()(domino_to_string(d));
        }
    };

    template<>
    struct less<domino_t>
    {
        bool operator()(const domino_t &a, const domino_t &b)
        {
            std::hash<domino_t> h;
            return h(a) < h(b);
        }
    };

    template<>
    struct equal_to<domino_t>
    {
        bool operator()(const domino_t &a, const domino_t &b)
        {
            std::hash<domino_t> h;
            return h(a) == h(b);
        }
    };

    template<>
    struct hash<domino_deque>
    {
        size_t operator()(const domino_deque &d) const
        {
            return std::hash<std::string>()(domino_deque_to_string(d));
        }
    };

    template<>
    struct less<domino_deque>
    {
        bool operator()(const domino_deque &a, const domino_deque &b)
        {
            std::hash<domino_deque> h;
            return h(a) < h(b);
        }
    };

    template<>
    struct equal_to<domino_deque>
    {
        bool operator()(const domino_deque &a, const domino_deque &b)
        {
            std::hash<domino_deque> h;
            return h(a) == h(b);
        }
    };



    template<>
    struct hash<domino_list>
    {
        size_t operator()(const domino_list &d) const
        {
            return std::hash<std::string>()(domino_list_to_string(d));
        }
    };

    template<>
    struct less<domino_list>
    {
        bool operator()(const domino_list &a, const domino_list &b)
        {
            std::hash<domino_list> h;
            return h(a) < h(b);
        }
    };

    template<>
    struct equal_to<domino_list>
    {
        bool operator()(const domino_list &a, const domino_list &b)
        {
            std::hash<domino_list> h;
            return h(a) == h(b);
        }
    };
}

#endif // DOMINO_FUNCTIONS_H
