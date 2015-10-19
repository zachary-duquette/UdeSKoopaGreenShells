#include <algorithm>

#include "WorldState.h"
#include "Player.h"
#include "Map"
#include "MapLocal.h"
#include "MapRemote.h"

#include <boost\property_tree\ptree.hpp>

using namespace std;

WorldState::WorldState()
	:m_map(nullptr), m_players(), m_mutex(), m_turn(1), m_remote(false)
{
	
}

WorldState::~WorldState()
{
}

Map* WorldState::GetMap()
{
	return m_map;
}

Map WorldState::GetMapCopy()
{
	lock_guard<recursive_mutex> lock{ m_mutex };
	return *m_map;
}

void WorldState::PrepareLocalGame()
{
	lock_guard<recursive_mutex> lock{ m_mutex };
	m_map = new MapLocal();
	m_map->GenerateTiles();
}

void WorldState::PrepareRemoteGame()
{
	lock_guard<recursive_mutex> lock{ m_mutex };
	m_map = new MapRemote();
	m_map->GenerateTiles();
}

int WorldState::GetCurrentTurn()
{
	lock_guard<recursive_mutex> lock{ m_mutex };
	return m_turn;
}

void WorldState::NotifyNewTurn()
{
	lock_guard<recursive_mutex> lock{ m_mutex };
	m_turn++;

	//Notify map of a new turn
	m_map->NotifyNewturn();

	//Notify players of a new turn
	for (Player& player : m_players)
	{
		if(player.IsAlive())
		{
			player.NotifyNewTurn();
		}
	}
}

int WorldState::AddPlayer(const Player& player)
{
	lock_guard<recursive_mutex> lock{ m_mutex };
	m_players.emplace_back(player);
	return static_cast<int>(m_players.size());
}

void WorldState::RemovePlayer(int id)
{
	lock_guard<recursive_mutex> lock{ m_mutex };
    for (Player &player : m_players)
    {
        if (player.GetPlayerID() == id)
        {
			player.SetDead();
            break;
        }
    }
}

boost::property_tree::ptree WorldState::Serialize()
{
	lock_guard<recursive_mutex> lock{ m_mutex };
    boost::property_tree::ptree worldStateXml;

    boost::property_tree::ptree& worldStateNode = worldStateXml.add("WS", "");

    // Get Player XML to add here
    boost::property_tree::ptree& playerListNode = worldStateNode.add("Ps", "");
    for (Player player : m_players)
    {
        playerListNode.add_child("P", player.Serialize());
    }

    // Get Map XML
    worldStateNode.add_child("M", m_map->Serialize());
    
    return worldStateXml;
}

void WorldState::Deserialize(boost::property_tree::ptree worldStateXml)
{
	lock_guard<recursive_mutex> lock{ m_mutex };

	m_turn = 0;
	m_players.clear();
	delete m_map;

    for each (auto worldStateNode in worldStateXml.get_child("WS"))
    {
        if (worldStateNode.first == "Ps")
        {
            for each (auto playerNode in worldStateNode.second)
            {
                AddPlayer(Player::Deserialize(playerNode.second));
            }
        }
        else if (worldStateNode.first == "M")
        {
			if (m_remote)
			{
				m_map = MapLocal::Deserialize(worldStateNode.second);
			}
			else
			{
				m_map = MapRemote::Deserialize(worldStateNode.second);
			}
        }
    }
}

Player WorldState::GetPlayer(int playerID)
{
	lock_guard<recursive_mutex> lock{ m_mutex };
	return m_players.at(playerID);
}

bool WorldState::AreAllPlayerReady()
{
	lock_guard<recursive_mutex> lock{ m_mutex };
	if (m_players.empty())
	{
		return false;
	}

	for (Player& player : m_players)
	{
		if (player.IsAlive() && !player.IsPlayerReadyForNextTurn())
		{
			return false;
		}
	}

	return true;
}