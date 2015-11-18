#include "AsyncBackTrackAlg.h"



bool CAsyncBackTrackAlg::Update()
{
	if (mpEntitityManager->UpdateMessages())
	{	
		for (auto i: *mpEntitityManager->GetAgentList())
		{
			if (i->NeedsUpdating())
			{
				if (!i->CheckConsistent())
				{
					if (!i->FindNewAssignment())
					{
						mSolutionExists = i->GenerateNoGood();
						while (mSolutionExists&&!i->FindNewAssignment())
						{
							mSolutionExists = i->GenerateNoGood();
						}

						//exit update if there is no longer a solution
						if (!mSolutionExists)
						{
							return false;
						}
					}
				}
			}
		}
	}
	else mSolved= true;
	return mSolutionExists;
}

bool CAsyncBackTrackAlg::SolutionExists()
{
	return mSolutionExists;
}

bool CAsyncBackTrackAlg::Solved()
{
	return mSolved;
}

void CAsyncBackTrackAlg::PrintSolution()
{
	for (auto i : *mpEntitityManager->GetAgentList())
	{
		std::cout << "piece : " << i->GetPriority() << " is in position :  " <<
			i->GetAssignment() << std::endl;
	}
}

void CAsyncBackTrackAlg::SetCurrentProblem(CEntityManager * problem)
{
	mpEntitityManager = problem;
}

CAsyncBackTrackAlg::CAsyncBackTrackAlg(CEntityManager * problem)
{
	mpEntitityManager = problem;
	mSolutionExists = true;
	mSolved = false;
}


CAsyncBackTrackAlg::~CAsyncBackTrackAlg()
{
}
