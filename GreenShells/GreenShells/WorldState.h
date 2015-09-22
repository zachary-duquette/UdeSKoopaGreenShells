#pragma once
#include <vector>
#include "Map.h"

class Player;

class WorldState
{
	std::vector<Player> m_players;	
	Map m_map;

public:
	WorldState();
	~WorldState();

	void AddPlayer(const Player& player);
	
	
	//temporary, will do a manager for UI
	Map GetMap();
};

