#pragma once
#include "Unit.h"
#include "RPCBase.h"


class UnitRemote : Unit, RPCBase
{
	UnitRemote(int id, const Position& pos);
	~UnitRemote();
};