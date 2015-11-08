#include "Agent.h"



void CAgent::AddToAgentView(SAgentV)
{
}

void CAgent::AddNoGood(int)
{
}

bool CAgent::FindNewAssignment()
{
	return false;
}

CAgent::CAgent(int Priority)
{
	mAssaignment = 1;
	mPriority = Priority;
	mNeedsUpdating = true;
}

CAgent::~CAgent()
{
}

bool CAgent::CheckConsistent()
{
	return false;
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

void CAgent::ReciveMessage(SMessage)
{
}
