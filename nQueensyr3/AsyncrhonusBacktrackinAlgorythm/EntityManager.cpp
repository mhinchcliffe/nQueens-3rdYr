#include "EntityManager.h"



CEntityManager::CEntityManager()
{
}


CEntityManager::~CEntityManager()
{
}

void CEntityManager::UpdateMessages()
{
}

int CEntityManager::GetNumAgents()
{
	return mAgentList.size();
}

std::vector<CAgent>* CEntityManager::GetAgentList()
{
	return &mAgentList;
}
