#pragma once
#include "EntityManager.h"
#include "Common.h"

class CAsyncBackTrackAlg
{
private:
	bool mSolutionExists;
	bool mSolved;
	CEntityManager* mpEntitityManager;

public:
	CAsyncBackTrackAlg(CEntityManager* problem);
	~CAsyncBackTrackAlg();
	// - Main Function - //
	bool Update();

	// - Getter - //
	bool SolutionExists();
	bool Solved();
	void PrintSolution();

	// - Setter - //
	void SetCurrentProblem(CEntityManager* problem);
};

