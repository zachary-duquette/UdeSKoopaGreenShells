#include "TileGround.h"


TileGround::TileGround(Position position)
:Tile(position)
{
}


TileGround::~TileGround()
{
}

bool TileGround::CanTraverse()
{
	return true;
}