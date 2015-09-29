#include <algorithm>

#include "WorldState.h"
#include "Player.h"
#include "MapLocal.h"

WorldState::WorldState()
:m_map(nullptr), m_players()
{
	
}

WorldState::~WorldState()
{
}

void WorldState::SetMap(Map* map)
{
	m_map = map;
}

Map* WorldState::GetMap()
{
	return m_map;
}

void WorldState::PrepareGame()
{
	m_map =	new MapLocal();
	m_map->GenerateTiles();
}

int WorldState::GetCurrentTurn()
{
	return m_turn;
}

void WorldState::NotifyNewTurn()
{
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

void WorldState::AddPlayer(const Player& player)
{
	m_players.emplace_back(player);
}

void WorldState::RemovePlayer(int id)
{
	for (Player &player : m_players)
	{
		if (player.GetPlayerID() == id)
		{
			player.SetDead();
			break;
		}
	}
}

Player & WorldState::GetPlayer(int playerID)
{
	return m_players.at(playerID);
}

bool WorldState::AreAllPlayerReady()
{
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