#pragma once
#include "EntityManager.h"
#include "Common.h"

class CAsyncBackTrackAlg
{
private:
	bool mSolutionExists;
	CEntityManager* mpEntitityManager;

public:
	CAsyncBackTrackAlg();
	~CAsyncBackTrackAlg();
	// - Main Function - //
	bool Update();

	// - Getter - //
	bool SolutionExists();

	// - Setter - //
	void SetCurrentProblem(CEntityManager* problem);
};

