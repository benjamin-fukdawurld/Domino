#ifndef DOMINO_TYPES_H
#define DOMINO_TYPES_H

#include <cstdint>
#include <utility>

#include <deque>
#include <list>

typedef std::pair<uint8_t, uint8_t> domino_t;

typedef std::deque<domino_t> domino_deque;

typedef std::list<domino_t> domino_list;

enum DominoInsertPosition
{
    Head,
    Tail
};

typedef std::pair<size_t, DominoInsertPosition> domino_move;

#endif // DOMINO_TYPES_H
