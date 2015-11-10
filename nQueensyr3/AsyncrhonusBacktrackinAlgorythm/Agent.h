#pragma once
#include "Messenger.h"
#include "Common.h"

class CAgent
{
protected:
	// - View of Other Agent Values - //
	std::vector<SAgentV> mAgentView;  // What this agent thinks the other agents assignments are
	std::vector<int> mNoGoodsList;	  // Values that are incopmpatible with lower priority agent

	// - Agents Values - //
	int mAssaignment;    // The agents current assignment
	int mPriority;       // Generally arbitrary, 
	int mNumPosibleAssignments;
	int mUID;
	bool mNeedsUpdating; //Wether or not this agent has recived a message since its last update
	CMessenger* mMessenger;
	// - Update Agent Constraints - //
	void AddToAgentView(SAgentV newView);
	void AddNoGood(int nogood);
	bool FindNewAssignment();

public:
	CAgent(int Priority, CMessenger* messenger);
	~CAgent();

	bool CheckConsistent();
	bool CheckConsistent(int i);
	bool GenerateNoGood();
	void ReciveMessage(SMessage message);

	// - Getters - //
	bool NeedsUpdating();
	int GetPriority();

};

