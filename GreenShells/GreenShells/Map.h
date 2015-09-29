#pragma once
#include "Position.h"
#include <vector>
#include "Tile.h"
#include "Texture.h"

class Map
{
protected:
	static const int ROWS = 64;
	static const int COLUMNS = 64;

	std::vector<std::vector<Tile*>> m_tiles;

public:
	Map();
	~Map();
	static Texture m_texture;

	void GenerateTiles();

	std::vector<Tile*> GetArea(Position position, int distance);

	Tile* GetTile(Position);
	virtual bool MoveUnit(int id, Position unitLocation, Position newLocation)=0;
	void NotifyNewturn();
};

