#include "Agent.h"



void CAgent::AddToAgentView(SAgentV newView)
{
	for (int i = 0; i < mAgentView.size();i++)
	{
		if (mAgentView[i].UID == newView.UID)
		{
			mAgentView[i].Value = newView.Value;
			return;
		}
	}
	mAgentView.push_back(newView);
}

void CAgent::RemoveFromAgentView(int agent)
{
	for (int i = 0; i < mAgentView.size();i++)
	{
		if (mAgentView[i].UID == agent)
		{
			mAgentView.erase(mAgentView.begin() + i);
		}
	}
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

bool CAgent::CheckIfAgentConsistent(SAgentV *agent)
{
	if (agent->Value == mAssaignment)
	{
		return false;
	}

	int lPriorityDiff = abs(agent->UID - mPriority);
	if (abs(agent->Value - mAssaignment) == lPriorityDiff)
	{
		return false;
	}
	return true;
}

bool CAgent::FindNewAssignment()
{
	bool lNewAssignmentFound = false;
	int tempassign = mAssaignment;
	for (int i = 0; i < mNumPosibleAssignments; i++)
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
			mAssaignment = i;
			lNewAssignmentFound = CheckConsistent(i);
		}
		//found new assignment
		if (lNewAssignmentFound)
		{
			mAssaignment = i;
			mMessenger->AddMessage(mUID, mUID, Ok, mAssaignment);
			return true;
		}
	}
	mAssaignment = tempassign;
	return false;//failed to find new assignment
}

CAgent::CAgent(int Priority,int numAssignments,int UID, CMessenger * messenger)
{
	mAssaignment = 0;
	mPriority = Priority;
	mNeedsUpdating = true;
	mNumPosibleAssignments = numAssignments;
	mUID = UID;
	mMessenger = messenger;
	mMessenger->AddMessage(mUID, mUID, Ok, mAssaignment);
}

CAgent::~CAgent()
{
}

bool CAgent::CheckConsistent()
{
	for (auto i : mAgentView)
	{
		if (!CheckIfAgentConsistent(&i))
		{
			return false;//vertical clash
		}
	}	
	mNeedsUpdating = false;
	return true;//no clash
}

bool CAgent::CheckConsistent(int value)
{
	for (int i = 0; i < mAgentView.size();i++)
	{
		if (!CheckIfAgentConsistent(&mAgentView[i]))
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

	for (int i = 0; i < mAgentView.size();i++)
	{
		if (!CheckIfAgentConsistent(&mAgentView[i]))
		{
			if (mAgentView[i].UID > lLowPriAgent)
			{
				lLowPriAgent = mAgentView[i].UID;
			}
		}
	}

	if (lLowPriAgent == mPriority)
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

int CAgent::GetAssignment()
{
	return mAssaignment;
}

void CAgent::ReciveMessage(SMessage *message)
{
	switch (message->Type)
	{
		case Ok:
			AddToAgentView(message->Message);
			break;
		case NoGood:
			AddNoGood(message->Message.Value);
		default:
			break;
	}
	mNeedsUpdating = true;
}
