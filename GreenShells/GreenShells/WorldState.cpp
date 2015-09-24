#include <algorithm>

#include "WorldState.h"
#include "Player.h"

#include <boost\property_tree\ptree.hpp>

WorldState::WorldState()
:m_map(), m_players()
{
	m_map.GenerateTiles();
}

WorldState::~WorldState()
{
}

void WorldState::PrepareGame()
{
	AddPlayer(Player());
}

void WorldState::AddPlayer(const Player& player)
{
	m_players.push_back(player);
}

void WorldState::RemovePlayer(int id)
{
	for (Player &player : m_players)
	{
		if (player.GetPlayerID() == id)
		{
			player.SetPlayerDead();
			break;
		}
	}
}

Map WorldState::GetMap()
{
    return m_map;
}

boost::property_tree::ptree WorldState::Serialize()
{
    boost::property_tree::ptree worldStateNode;

    
    return worldStateNode;
}
