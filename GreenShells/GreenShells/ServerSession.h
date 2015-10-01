#pragma once
#include "RPCManager.h"
#include "RPCDispatcher.h"
#include "SynchronizedQueue.h"
#include "WorldState.h"

class ServerSession
{
	RPCDispatcher* m_dispatcher;
	RPCManager* m_rpcServerManager;
	SynchronizedQueue<RPCEvent> m_events;
	WorldState m_worldState;

	std::thread* m_serverSessionThread;

	ServerSession();
	ServerSession(ServerSession const&) = delete;
	void operator = (ServerSession const&) = delete;

	void run();
public:
	static ServerSession &GetInstance()
	{
		static ServerSession m_serverSession;
		return m_serverSession;
	}
	~ServerSession();

	void StartServer(int port);

};





