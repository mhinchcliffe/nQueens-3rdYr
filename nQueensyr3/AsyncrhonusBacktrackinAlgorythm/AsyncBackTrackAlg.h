#pragma once
#include "EntityManager.h"
#include "Common.h"

class CAsyncBackTrackAlg
{
private:
	bool mSolutionExists;

public:
	
	CAsyncBackTrackAlg();
	~CAsyncBackTrackAlg();
	// - Main Function - //
	bool Update(std::vector<CAgent>* AgentList);

	// - Getter - //
	bool SolutionExists();
};

