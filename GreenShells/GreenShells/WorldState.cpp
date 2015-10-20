#include <algorithm>
#include <iostream>
#include <boost\property_tree\ptree.hpp>

#include "WorldState.h"
#include "Player.h"
#include "Map"
#include "MapLocal.h"
#include "MapRemote.h"
#include "Settler.h"
#include "TileBase.h"

using namespace std;

WorldState::WorldState()
:m_map(nullptr), m_players(), m_mutex(), m_turn(1)
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
		player.NotifyNewTurn();
	}
}

int WorldState::AddPlayer(std::string playerName)
{
	lock_guard<recursive_mutex> lock{ m_mutex };

	for (auto player: m_players)
	{
		if (playerName == player.GetPlayerName())
		{
			//it's a reconnect
			std::cout << playerName << " has reconnected!" << endl;
			player.SetIsDisconnected(false);
			return player.GetPlayerID();
		}
	}

	std::cout << playerName << " has joined." << endl;
	int playerID = static_cast<int>(m_players.size());
	Player newPlayer;
	newPlayer.SetPlayerID(playerID);
	newPlayer.SetPlayerName(playerName);
	Position spawnPosition = m_map->GetSpawnPositions()[playerID];
	TileBase* tile = m_map->GetTile(spawnPosition);
	tile->SetUnit(new Settler(playerID));
	m_players.push_back(newPlayer);
	return playerID;
}

void WorldState::RemovePlayer(int id)
{
	lock_guard<recursive_mutex> lock{ m_mutex };
    for (Player &player : m_players)
    {
        if (player.GetPlayerID() == id)
        {
			player.SetIsAlive(false);
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
				m_players.push_back(Player::Deserialize(playerNode.second));
                //AddPlayer();
            }
        }
        else if (worldStateNode.first == "M")
        {
            m_map = MapLocal::Deserialize(worldStateNode.second);
			// TODO :  need to know from wich class we need to Deserialize, cause map is abstract (bool in WorldState)
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