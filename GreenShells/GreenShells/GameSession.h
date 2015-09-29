#pragma once
#include "WorldState.h"
#include <string>

class RPCManager;

class GameSession
{
	WorldState m_worldState;

	bool m_isServer;
	std::string m_serverIP;
	int m_port;

	RPCManager* m_rpcServerManager;

	GameSession();

	GameSession(GameSession const&) = delete;
	void operator = (GameSession const&) = delete;
public:
	static GameSession &GetGameSession()
	{
		static GameSession m_gameSession;
		return m_gameSession;
	}
	~GameSession();

	WorldState* GetWorldState();
	void SetIsServer(bool isServer);
	bool IsServer();

	void SetServerIP(std::string ip);
	std::string GetServerIP();

	void SetPort(int port);
	int GetPort();

	bool ConnectToServer();
	void PrepareGame();
};

