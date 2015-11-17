#include "AsyncBackTrackAlg.h"



bool CAsyncBackTrackAlg::Update()
{
	if (mpEntitityManager->UpdateMessages())
	{
		std::vector<CAgent*>* lTempList = mpEntitityManager->GetAgentList();
		
		for (auto i: *lTempList)
		{
			if (!i->NeedsUpdating())
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
	return mSolutionExists;
}

bool CAsyncBackTrackAlg::SolutionExists()
{
	return mSolutionExists;
}

void CAsyncBackTrackAlg::SetCurrentProblem(CEntityManager * problem)
{
	mpEntitityManager = problem;
}

CAsyncBackTrackAlg::CAsyncBackTrackAlg()
{
}


CAsyncBackTrackAlg::~CAsyncBackTrackAlg()
{
}
