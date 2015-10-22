#pragma once

#include <string>
#include "Position.h"

using namespace std;

/*
When creating a new struct to send over the network, don't forget to add the corresponding name in the enum 
*/
struct PlayerInfoStruct
{
	int playerID;
	char playerName[50];

	void setPlayerName(std::string name)
	{
		strncpy_s(playerName, name.c_str(), sizeof(playerName));
		playerName[sizeof(playerName) - 1] = 0;
	}

	std::string getPlayerName()
	{
		return string(playerName);
	}
};


enum RPCStructType
{
	RPC_BASIC,
	RPC_BASIC_TWO_POSITIONS,

};

enum RPCClassMethodType
{
	//Class_Method,
	Map_Move,
	Map_Attack

};

struct RPCBasicStruct
{
	int m_turn;
	int m_requestingPlayerID;
	RPCClassMethodType m_RPCClassMethod;

	virtual bool virtualMethodForCompile()
	{ return false;	}
};

struct RPCBasicTwoPositionsStruct : public RPCBasicStruct
{
	Position m_firstPosition;
	Position m_secondPosition;
};

struct RPCEvent
{
	RPCStructType structType;
	RPCBasicStruct* data;
};