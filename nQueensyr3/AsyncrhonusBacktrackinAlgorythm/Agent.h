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
	void RemoveFromAgentView(int agent);
	void AddNoGood(int nogood);
	bool CheckIfAgentConsistent(SAgentV *agent);//checks to see if an agents assignment is incompatible with this agents values

public:
	CAgent(int Priority,int NumAssignments, int UID,CMessenger* messenger);
	~CAgent();

	bool CheckConsistent();
	bool CheckConsistent(int i);
	bool GenerateNoGood();
	bool FindNewAssignment();
	void ReciveMessage(SMessage *message);

	// - Getters - //
	bool NeedsUpdating();
	int GetPriority();
	int GetAssignment();
};

