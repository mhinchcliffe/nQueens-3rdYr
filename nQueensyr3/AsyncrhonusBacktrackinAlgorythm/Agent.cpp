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

bool CAgent::FindNewAssignment()
{
	bool lNewAssignmentFound;

	for (int i = 1; i <= mNumPosibleAssignments; i++)
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
		if (lNewAssignmentFound)
		{
			mAssaignment = i;
			return true;
		}
	}
	return false;
}

CAgent::CAgent(int Priority)
{
	mAssaignment = 1;
	mPriority = Priority;
	mNeedsUpdating = true;
	mNumPosibleAssignments = 4;
	mUID = Priority;
}

CAgent::~CAgent()
{
}

bool CAgent::CheckConsistent()
{
	for (auto i : mAgentView)
	{
		if (i.Value == mAssaignment)
		{
			return false;
		}
	}
	for (auto i : mAgentView)
	{
		int lPriorityDiff = abs(i.UID - mPriority);
		if (abs(i.Value-mAssaignment)==lPriorityDiff)
		{
			return false;
		}
	}
	return true;
}

bool CAgent::CheckConsistent(int value)
{
	for (auto i : mAgentView)
	{
		if (i.Value == value)
		{
			return false;
		}
	}
	for (auto i : mAgentView)
	{
		//if the diffrence in rows is equal to the diffrence in colmns, then the piece can be taken diagonally
		int lPriorityDiff = abs(i.UID - value);
		if (abs(i.Value - value) == lPriorityDiff)
		{
			return false;
		}
	}
	return true;
}

bool CAgent::GenerateNoGood()
{
	return false;
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
