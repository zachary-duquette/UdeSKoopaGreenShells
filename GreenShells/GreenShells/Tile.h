#pragma once
#include "Position.h"

class District;
class Unit;
class Player;

namespace boost
{
    namespace property_tree
    {
        template < class Key, class Data, class KeyCompare >
        class basic_ptree;

        typedef basic_ptree< std::string, std::string, std::less<std::string> > ptree;
    }
}


class Tile 
{
protected:
    District* m_district;
    Unit* m_unit;
    int m_owner;

public:
    Position m_position;
    Tile(Position position);
    Tile();
    ~Tile();

    virtual boost::property_tree::ptree Serialize();
    virtual Tile Deserialize(boost::property_tree::ptree tileNode);
};

