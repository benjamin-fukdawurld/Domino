#include "Domino_functions.h"

#include <cassert>
#include <cstring>
#include <sstream>

uint8_t domino_attachPoint(const domino_t &d1, const domino_t &d2)
{
    return (d1.first == d2.first || d1.first == d2.second ? d1.first
                                                          : (d1.second == d2.first || d1.second == d2.second ? d1.second : 255));
}

bool domino_canAttach(const domino_t &d1, const domino_t &d2)
{
    return d1.first == d2.first || d1.first == d2.second
            || d1.second == d2.first || d1.second == d2.second;
}

std::ostream &domino_print(const domino_t & d, std::ostream &out)
{
    return out << static_cast<int>(d.first) << " / " << static_cast<int>(d.second);
}

std::istream &domino_scan(domino_t &d, std::istream &in)
{
    int buff = -1;
    in >> buff;
    assert(buff >= 0 && buff <= 6);
    d.first = static_cast<uint8_t>(buff);
    in.ignore();
    in.ignore();
    in.ignore();
    in >> buff;
    assert(buff >= 0 && buff <= 6);
    d.first = static_cast<uint8_t>(buff);
    in.ignore();
    in.ignore();
    in.ignore();
    return in;
}

std::string domino_to_string(const domino_t &domino)
{
    return std::to_string(domino.first) + " / " + std::to_string(domino.second);
}

void domino_reverse(domino_t &domino)
{
    std::swap(domino.first, domino.second);
}

size_t domino_id(domino_t domino)
{
    if(domino.first > domino.second)
        domino_reverse(domino);

    size_t result = 0;
    for(uint8_t i = 0; i < domino.first; ++i)
        result += 7 - i;

    return result + domino.second - domino.first;
}

std::ostream &operator<<(std::ostream &out, const domino_t &domino)
{
    return domino_print(domino, out);
}

std::istream &operator>>(std::istream &in, domino_t &domino)
{
    return domino_scan(domino, in);
}

std::ostream &operator<<(std::ostream &out, const domino_deque &dominos)
{
    return domino_deque_print(dominos, out);
}

std::istream &operator>>(std::istream &in, domino_deque &dominos)
{
    return domino_deque_scan(dominos, in);
}

std::ostream &domino_deque_print(const domino_deque &dominos, std::ostream &out)
{
    if(dominos.empty())
        return out;

    out << domino_to_string(dominos[0]);
    for(size_t i = 1; i < dominos.size(); ++i)
        out << " " << domino_to_string(dominos[i]);

    return out;
}

std::istream &domino_deque_scan(domino_deque &dominos, std::istream &in)
{
    while(!in.eof())
    {
        domino_t d;
        in >> d;
        dominos.push_back(std::move(d));
        in.ignore();
    }

    return in;
}

std::string domino_deque_to_string(const domino_deque &domino)
{
    std::ostringstream oss;
    oss << domino;
    return oss.str();
}

std::ostream &domino_list_print(const domino_list &dominos, std::ostream &out)
{
    if(dominos.empty())
        return out << "[]";

    auto it = dominos.begin();
    out << "[" << *it;
    ++it;
    for(; it != dominos.end(); ++it)
        out << ", " << *it;

    return out << "]";
}

std::istream &domino_list_scan(domino_list &dominos, std::istream &in)
{
    char buff[256] = {0};
    in.getline(buff, 256, ']');
    if(buff[1] == ']')
        return in;

    std::istringstream iss(std::string(buff + 1, strlen(buff + 1) - 1));

    if(iss.eof())
        return in;

    {
        domino_t d;
        in >> d;
        dominos.push_back(std::move(d));
    }

    while(!iss.eof())
    {
        in.ignore();
        in.ignore();
        domino_t d;
        in >> d;
        dominos.push_back(std::move(d));
    }

    return in;
}

std::string domino_list_to_string(const domino_list &dominos)
{
    std::ostringstream oss;
    oss << dominos;
    return  oss.str();
}

std::ostream &operator<<(std::ostream &out, const domino_list &dominos)
{
    return domino_list_print(dominos, out);
}

std::istream &operator>>(std::istream &out, domino_list &dominos)
{
    return domino_list_scan(dominos, out);
}

rapidjson::Value domino_to_json(const domino_t &domino, rapidjson::Document &doc)
{
    rapidjson::Value result(rapidjson::kArrayType);
    result.PushBack(domino.first, doc.GetAllocator());
    result.PushBack(domino.second, doc.GetAllocator());
    return result;
}

bool domino_from_json(domino_t &domino, const rapidjson::Value &val)
{
    if(!val.IsArray() || val.Size() != 2)
        return  false;

    domino.first = static_cast<uint8_t>(val[0].GetUint());
    domino.second = static_cast<uint8_t>(val[1].GetUint());
    return true;
}

rapidjson::Value domino_deque_to_json(const domino_deque &domino, rapidjson::Document &doc)
{
    rapidjson::Value result(rapidjson::kArrayType);
    for(auto &d : domino)
        result.PushBack(domino_to_json(d, doc), doc.GetAllocator());
    return result;
}

rapidjson::Value domino_list_to_json(const domino_list &domino, rapidjson::Document &doc)
{
    rapidjson::Value result(rapidjson::kArrayType);
    for(auto &d : domino)
        result.PushBack(domino_to_json(d, doc), doc.GetAllocator());
    return result;
}

bool domino_deque_from_json(domino_deque &domino, const rapidjson::Value &val)
{
    if(!val.IsArray())
        return  false;

    for(rapidjson::SizeType i = 0; i < val.Size(); ++i)
    {
        domino_t d;
        if(!domino_from_json(d, val[i]))
            return false;

        domino.push_back(d);
    }

    return true;
}

bool domino_list_from_json(domino_list &domino, const rapidjson::Value &val)
{
    if(!val.IsArray())
        return  false;

    for(rapidjson::SizeType i = 0; i < val.Size(); ++i)
    {
        domino_t d;
        if(!domino_from_json(d, val[i]))
            return false;

        domino.push_back(d);
    }

    return true;
}

std::string DominoInsertPosition_to_string(DominoInsertPosition pos)
{
    switch (pos)
    {
        case Head:
        return "Head";

        case Tail:
        return "Tail";
    }

    return "Invalid";
}

DominoInsertPosition DominoInsertPosition_from_string(std::string_view pos)
{
    return pos == "Head" ? Head : Tail;
}

rapidjson::Value DominoInsertPosition_to_json(DominoInsertPosition pos, rapidjson::Document &)
{
    return pos == Head ? rapidjson::Value("Head", 4) : rapidjson::Value("Tail", 4);
}

bool DominoInsertPosition_from_json(DominoInsertPosition &pos, const rapidjson::Value &val)
{
    if(!val.IsString())
        return false;

    pos = DominoInsertPosition_from_string(std::string(val.GetString()));
    return true;
}

std::string domino_move_to_string(const domino_move &move)
{
    return std::to_string(move.first) + " | " + DominoInsertPosition_to_string(move.second);
}

rapidjson::Value domino_move_to_json(const domino_move &move, rapidjson::Document &doc)
{
    rapidjson::Value result(rapidjson::kObjectType);
    result.AddMember(rapidjson::Value("move", 4),
                     rapidjson::Value(move.first),
                     doc.GetAllocator());

    result.AddMember(rapidjson::Value("pos", 3),
                     DominoInsertPosition_to_json(move.second, doc),
                     doc.GetAllocator());

    return result;
}

bool domino_move_from_json(domino_move &move, const rapidjson::Value &val)
{
    if(!val.IsObject() || !val.HasMember("move") || !val.HasMember("pos"))
        return false;

    move.first = val["move"].GetUint();
    return DominoInsertPosition_from_json(move.second, val["pos"]);
}
