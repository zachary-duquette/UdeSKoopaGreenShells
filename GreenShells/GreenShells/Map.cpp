#include "Map.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"
#include "DistrictCityCenter.h"

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
    for (std::vector<TileBase*> tileRow : m_tiles)
    {
        for (TileBase* tile : tileRow)
        {
            delete tile;
        }
    }
}

void Map::GenerateTiles()
{
    std::ifstream ifs{ "Ressources\\maps\\FirstMap.txt" };

    assert(ifs.good() && "Make sure you have the ressources folder beside your exe.");

    std::string map((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());

    map.erase(std::remove(map.begin(), map.end(), '\n'), map.end());
    for (int row = 0; row < ROWS; ++row)
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
            char tileType = map.at((row * ROWS) + column);
            switch (tileType)
            {
            default:
            case '0':
                m_tiles[row][column] = new TileGround(Position(column, row));
                break;

            case '1':
                m_tiles[row][column] = new TileMountain(Position(column, row));
                break;

            case '2':
                m_tiles[row][column] = new TileWater(Position(column, row));
                break;

            case '3':
                Position position(column, row);
                m_tiles[row][column] = new TileGround(position);
                m_spawnPositions.push_back(position);
                break;
            }
        }
    }

	int playerId = 0;
	for (Position spawn : m_spawnPositions)
	{
		m_tiles[spawn.Row][spawn.Column]->SetDistrict(new DistrictCityCenter(playerId));
		for (int i = spawn.Row - 3; i < spawn.Row + 4; ++i)
		{
			for (int j = spawn.Column - 1; j < spawn.Column + 2; ++j)
			{
				m_tiles[i][j]->SetPlayerOwnerId(playerId);
			}
		}
		++playerId;
	}
}

std::vector<Position> Map::GetSpawnPositions()
{
    return m_spawnPositions;
}

std::vector<Position> Map::GetArea(Position position, int distance)
{
    std::vector<Position> area;

    //find miminum and maximum
    int maxCol = position.Column + distance;
    int maxRow = position.Row + distance;

    int minCol = position.Column - distance;
    if (minCol < 0)
    {
        minCol += COLUMNS;
        maxCol += COLUMNS;
    }
    int minRow = position.Row - distance;
    if (minRow < 0)
    {
        minRow += ROWS;
        maxRow += ROWS;
    }

    for (int row = minRow; row <= maxRow; ++row)
    {
        for (int column = minCol; column <= maxCol; ++column)
        {
            area.push_back(Position(column % COLUMNS, row % ROWS));
        }
    }
    return area;
}

TileBase* Map::GetTile(Position position)
{
    return m_tiles[position.Row][position.Column];
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

    boost::property_tree::ptree& spawnListNode = mapNode.add("SPS", "");
    for (int i = 0; i < m_spawnPositions.size(); ++i)
    {
        boost::property_tree::ptree& spawnNode = spawnListNode.add("SP", "");
        spawnNode.put("<xmlattr>.X", m_spawnPositions[i].Column);
        spawnNode.put("<xmlattr>.Y", m_spawnPositions[i].Row);
    }

    for (int row = 0; row < ROWS; ++row)
    {
        boost::property_tree::ptree& rowNode = mapNode.add("R", "");
        for (int column = 0; column < COLUMNS; ++column)
        {
            boost::property_tree::ptree& tileNode = m_tiles[row][column]->Serialize();
            rowNode.add_child("T", tileNode);
        }
    }

    return mapNode;
}

bool Map::MoveUnit(int ownerID, Position unitLocation, Position newLocation)
{
    assert(false && "Virtual method is not implemented");
    return false;
}

bool Map::Attack(int ownerID, Position attackerPosition, Position targetPosition)
{
	assert(false && "Virtual method is not implemented");
	return false;
}

bool Map::CreateDistrict(int unitType, Position pos, int owner)
{
	assert(false && "Virtual method is not implemented");
	return false;
}

bool Map::CreateUnit(int districtType, Position pos, int owner)
{
    assert(false && "Virtual method is not implemented");
    return false;
}