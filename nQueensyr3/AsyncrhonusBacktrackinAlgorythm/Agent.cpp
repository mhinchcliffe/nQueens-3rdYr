#include "Agent.h"



void CAgent::AddToAgentView(SAgentV newView)
{
	for (auto i: mAgentView) 
	{
		if (i.UID == newView.UID)
		{
			i.Value = newView.Value;
			return;
		}
	}
	mAgentView.push_back(newView);
}

void CAgent::RemoveFromAgentView(int agent)
{
	/*for (auto i : mAgentView)
	{
		if (i.UID == agent)
		{
			auto it = std::find(mAgentView.begin(), mAgentView.end(), i);
			if (it != mAgentView.end())
			{
				mAgentView.erase(it);
			}
		}
	}*/
}

void CAgent::AddNoGood(int nogood)
{
	for (auto i : mNoGoodsList)
	{
		if (i == nogood)
		{
			return;
		}
	}
	mNoGoodsList.push_back(nogood);
}

bool CAgent::CheckIfAgentConsistent(SAgentV agent)
{
	if (agent.Value == mAssaignment)
	{
		return false;
	}

	int lPriorityDiff = abs(agent.UID - mPriority);
	if (abs(agent.Value - mAssaignment) == lPriorityDiff)
	{
		return false;
	}
	return true;
}

bool CAgent::FindNewAssignment()
{
	bool lNewAssignmentFound = false;

	for (int i = 0; i <= mNumPosibleAssignments; i++)
	{
		lNewAssignmentFound = true;
		//check new assignment against nogood list
		for (int j = 0; lNewAssignmentFound == true && j < mNoGoodsList.size();j++)
		{
			if (mNoGoodsList[j] == i)
			{
				lNewAssignmentFound = false;
			}
		}
		//check new assignment against agent view
		if (lNewAssignmentFound)
		{
			lNewAssignmentFound = CheckConsistent(i);
		}
		//found new assignment
		if (lNewAssignmentFound)
		{
			mAssaignment = i;
			mMessenger->AddMessage(mUID, mUID, Ok, mAssaignment);
			return lNewAssignmentFound;
		}
	}
	return lNewAssignmentFound;//failed to find new assignment
}

CAgent::CAgent(int Priority,int numAssignments,int UID, CMessenger * messenger)
{
	mAssaignment = 0;
	mPriority = Priority;
	mNeedsUpdating = true;
	mNumPosibleAssignments = numAssignments;
	mUID = UID;
	mMessenger = messenger;
}

CAgent::~CAgent()
{
}

bool CAgent::CheckConsistent()
{
	for (auto i : mAgentView)
	{
		if (CheckIfAgentConsistent(i))
		{
			return false;//vertical clash
		}
	}	
	mNeedsUpdating = false;
	return true;//no clash
}

bool CAgent::CheckConsistent(int value)
{
	for (auto i : mAgentView)
	{
		if (!CheckIfAgentConsistent(i))
		{
			return false;
		}
	}
	mNeedsUpdating = false;
	return true;
}

bool CAgent::GenerateNoGood()
{
	int lLowPriAgent=0;

	for (auto i : mAgentView)
	{
		if (!CheckIfAgentConsistent(i))
		{
			if (i.UID > lLowPriAgent)
			{
				lLowPriAgent = i.UID;
			}
		}
	}

	if (lLowPriAgent == 0)
	{
		return false;
	}
	else
	{
		mMessenger->AddMessage(lLowPriAgent, mUID, NoGood, mAssaignment);
		RemoveFromAgentView(lLowPriAgent);
		return true;
	}
}

bool CAgent::NeedsUpdating()
{
	return mNeedsUpdating;
}

int CAgent::GetPriority()
{
	return mPriority;
}

void CAgent::ReciveMessage(SMessage message)
{
	switch (message.Type)
	{
		case Ok:
			AddToAgentView(message.Message);
			break;
		case NoGood:
			AddNoGood(message.Message.Value);
		default:
			break;
	}
	mNeedsUpdating = true;
}
