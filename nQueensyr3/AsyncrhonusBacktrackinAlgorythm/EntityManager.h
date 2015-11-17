#pragma once
#include "Agent.h"
#include "Messenger.h"
#include "Common.h"

class CEntityManager
{
private:
	std::map<int, std::deque<SMessage>> mAgentMessageList;// uidto, double endded que of messages to that uid
	std::vector<CAgent*> mAgentList;
	CMessenger* mMessenger;
	void mUpdateMessageList();
	
public:

	CEntityManager(int NumAgents);
	~CEntityManager();

	// - Update Agents - //
	bool UpdateMessages();

	// - Getters - //
	int GetNumAgents();
	std::vector<CAgent*>* GetAgentList();
};

