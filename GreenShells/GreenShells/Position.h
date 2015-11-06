#pragma once
#include <string>

class Position
{
public:

    int Column;
    int Row;

    Position(int column = -1, int row = -1);
    ~Position();
    std::string ToString() const;

    friend std::ostream& operator<<(std::ostream& os, const Position& obj)
    {
        os << obj.ToString();
        return os;
    }

    inline bool operator == (const Position& other) { return Row == other.Row && Column == other.Column; }
    inline bool operator!=( const Position& other) { return !(*this == other); }
};