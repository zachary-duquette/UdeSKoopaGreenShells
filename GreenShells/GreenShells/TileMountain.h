#pragma once
#include "Tile.h"
class TileMountain :
	public Tile<TileMountain>
{

public:
	static const int TILE_TYPE = 1;
	typedef Tile<TileMountain> tBase;
	void LoadTexture();
	TileMountain(Position position);
	~TileMountain();
	virtual bool CanTraverse();	
	virtual int GetTypeAsInt();
	//virtual boost::property_tree::ptree Serialize();
	static TileMountain* Deserialize(boost::property_tree::ptree tileNode, Position pos = Position{ -1, 0 });
};

