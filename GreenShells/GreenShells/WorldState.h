#pragma once
#include <vector>
#include <mutex>
#include "Position.h"
#include "Ptree_ForwardDeclaration.h"

class Player;
class Map;

class WorldState
{
	std::recursive_mutex m_mutex;
	int m_turn;
	std::vector<Player> m_players;
	Map* m_map;
public:
	WorldState();
	~WorldState();

	//Temp Hack
	Map* GetMap();
	//Returns a copy of the map for drawing
	Map GetMapCopy();

	void PrepareLocalGame();
	void PrepareRemoteGame();
	int GetCurrentTurn();
	void NotifyNewTurn();

	int AddPlayer(std::string playerName);
	void RemovePlayer(int id);
	Player GetPlayer(int playerID);

	bool AreAllPlayerReady();
	boost::property_tree::ptree Serialize();
	void Deserialize(boost::property_tree::ptree worldStateXml);
};

