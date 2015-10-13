#pragma once

#include "SynchronizedQueue.h"
#include "RPCStructs.h"

class WorldState;

class RPCDispatcher
{
	SynchronizedQueue<RPCEvent>* m_queue;
	WorldState* m_worldState;

	void Dispatch(RPCBasicStruct* data);
	void Dispatch(RPCBasicTwoPositionsStruct* data);
	void Dispatch(RPCEvent);

public:
	RPCDispatcher();
	~RPCDispatcher();

	void SetWorldState(WorldState* worldState);
	WorldState* GetWorldState();

	void SetEventQueue(SynchronizedQueue<RPCEvent>* queue);
	SynchronizedQueue<RPCEvent>* GetEventQueue();

	void Dispatch();
};