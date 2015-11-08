#pragma once
#include "Agent.h"
#include "Messenger.h"
#include "Common.h"

class CEntityManager
{
private:
	std::map<int, std::deque<SMessage>> mAgentMessageList;// uidto, double endded que of messages to that uid
	std::vector<CAgent> mAgentList;
public:
	CEntityManager();
	~CEntityManager();
	// - Update Agents - //
	void UpdateMessages();

	// - Getters - //
	int GetNumAgents();
	std::vector<CAgent>* GetAgentList();
};

