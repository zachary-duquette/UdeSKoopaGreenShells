#include <sstream>
#include "MapRemote.h"
#include "RPCStructs.h"
#include "GameSession.h"

#include "TileGround.h"
#include "TileMountain.h"
#include "TileWater.h"
#include <boost\property_tree\ptree.hpp>

MapRemote::MapRemote()
	:Map()
{
}

MapRemote::~MapRemote()
{
}

bool MapRemote::MoveUnit(int ownerID, Position unitLocation, Position newLocation)
{
	//TODO Add checks on client to make sure that you can move this unit.
	std::stringstream ss;

	RPCStructType dataType{};
	dataType = RPCStructType::RPC_BASIC_TWO_POSITIONS;
	ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

	RPCBasicTwoPositionsStruct data;
	data.m_RPCClassMethod = RPCClassMethodType::Map_Move;
	data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
	data.m_requestingPlayerID = ownerID;
	data.m_firstPosition = unitLocation;
	data.m_secondPosition = newLocation;

	ss.write(reinterpret_cast<char*>(&data), sizeof(data));

	return SendData(ss.str());
}

bool MapRemote::Attack(int ownerID, Position attackerPosition, Position targetPosition)
{
	//TODO Add checks on client to make sure that you can attack this Actor.
	std::stringstream ss;

	RPCStructType dataType{};
	dataType = RPCStructType::RPC_BASIC_TWO_POSITIONS;
	ss.write(reinterpret_cast<char*>(&dataType), sizeof(dataType));

	RPCBasicTwoPositionsStruct data;
	data.m_RPCClassMethod = RPCClassMethodType::Map_Attack;
	data.m_turn = GameSession::GetInstance().GetWorldState()->GetCurrentTurn();
	data.m_requestingPlayerID = ownerID;
	data.m_firstPosition = attackerPosition;
	data.m_secondPosition = targetPosition;

	ss.write(reinterpret_cast<char*>(&data), sizeof(data));

	return SendData(ss.str());
}

MapRemote* MapRemote::Deserialize(boost::property_tree::ptree mapNode)
{
	MapRemote* map = new MapRemote();
	int y = 0;
	for each (auto rowNode in mapNode)
	{
		int x = 0;
		for each(auto tileNode in rowNode.second)
		{
			if (tileNode.first == "T")
			{
				Position pos{ x, y };

				switch (tileNode.second.get<int>("<xmlattr>.TT"))
				{
				case 0:
					map->m_tiles[pos.X][pos.Y] = TileGround::Deserialize(tileNode.second, pos);
					break;
				case 1:
					map->m_tiles[pos.X][pos.Y] = TileMountain::Deserialize(tileNode.second, pos);
					break;
				case 2:
					map->m_tiles[pos.X][pos.Y] = TileWater::Deserialize(tileNode.second, pos);
					break;

				case -1:
				default:
					std::string msg = ("Error while loading the map, a tile is of type unknown.");
					throw new std::exception(msg.c_str());
					break;
				}
			}
			x++;
		}
		y++;
	}

	return map;
}
