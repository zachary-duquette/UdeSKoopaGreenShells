#include "Map.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"

#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <assert.h>
#include <boost\property_tree\ptree.hpp>

Map::Map()
:m_tiles()
{
	for (int i = 0; i < ROWS; i++)
	{
		m_tiles.push_back(std::vector<TileBase*>(COLUMNS));
	}
}


Map::~Map()
{
}

void Map::GenerateTiles()
{
    std::ifstream ifs{ "Ressources\\maps\\FirstMap.txt" };

	assert(ifs.good() && "Make sure you have the ressources folder beside your exe." );

    std::string map((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());

    map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLUMNS; ++j)
        {
            char tileType = map.at((i * ROWS) + j);
            switch (tileType)
            {
            case '0':
				m_tiles[i][j] = new TileGround(Position(j, i));
                break;

            case '1':
				m_tiles[i][j] = new TileMountain(Position(j, i));
                break;

            case '2':
            default:
				m_tiles[i][j] = new TileWater(Position(j, i));
                break;
            }
        }
    }
}

std::vector<TileBase*> Map::GetArea(Position position, int distance)
{
	std::vector<TileBase*> area;

    //find miminum and maximum
    int minCol = std::max(position.X - distance, 0);
    int minRow = std::max(position.Y - distance, 0);
    int maxCol = std::min(position.X + distance, COLUMNS-1);
    int maxRow = std::min(position.Y + distance, ROWS-1);

    for (int i = minCol; i <= maxCol; ++i)
    {
        for (int j = minRow; j <= maxRow; ++j)
        {
            area.push_back(GetTile(Position(i, j)));
        }
    }
    return area;
}

TileBase* Map::GetTile(Position position)
{
    return m_tiles[position.Y][position.X];
}

void Map::NotifyNewturn()
{
	for (std::vector<TileBase*>& tileRow : m_tiles)
	{
		for (TileBase* tile : tileRow)
		{
			tile->NotifyNewTurn();
		}
		
	}
}

boost::property_tree::ptree Map::Serialize()
{
    boost::property_tree::ptree mapNode;

    for (int i = 0; i < ROWS; ++i)
    {
        boost::property_tree::ptree& rowNode = mapNode.add("Row", "");
        rowNode.put("<xmlattr>.Number", i);
        for (int j = 0; j < COLUMNS; ++j)
        {
            boost::property_tree::ptree& tileNode = m_tiles[i][j]->Serialize();
            rowNode.add_child("Tile", tileNode);            
        }
    }
            
    return mapNode;


}

