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

	bool mNeedsUpdating; //Wether or not this agent has recived a message since its last update

	// - Update Agent Constraints - //
	void AddToAgentView(SAgentV);
	void AddNoGood(int);
	bool FindNewAssignment();

public:
	CAgent(int Priority);
	~CAgent();

	bool CheckConsistent();
	bool GenerateNoGood();
	void ReciveMessage(SMessage);

	// - Getters - //
	bool NeedsUpdating();
	int GetPriority();

};

