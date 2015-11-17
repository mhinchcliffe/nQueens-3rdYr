#include "EntityManager.h"



void CEntityManager::mUpdateMessageList()
{
	while (!mMessenger->IsMessgeListEmpty())
	{
		SMessage temp = mMessenger->GetNextMessage();
		switch (temp.Type)
		{
		case Ok:
			for (int i = temp.UIDto + 1; i < mAgentList.size(); i++)
			{
				mAgentMessageList[i].push_back(temp);
			}
			break;
		case NoGood:
			mAgentMessageList[temp.UIDto].push_back(temp);
			break;
		default:
			break;
		}

	}
}

CEntityManager::CEntityManager(int NumAgents)
{
	mMessenger = new CMessenger;
	for (int i = 0; i < NumAgents; i++)
	{
		CAgent*temp = new CAgent(i,mMessenger);
		mAgentList.push_back(temp);
		std::deque<SMessage> empty;
		mAgentMessageList[i] = empty;
	}
}


CEntityManager::~CEntityManager()
{
	if (mMessenger != nullptr)
	{
		delete mMessenger;
		mMessenger = nullptr;
	}

	for (auto i : mAgentList)
	{
		if (i != nullptr)
		{
			delete i;
			i = nullptr;
		}
	}
}

bool CEntityManager::UpdateMessages()
{
	bool lNotEmpty = false;
	mUpdateMessageList();
	for (auto i : mAgentList)
	{
		if (!mAgentMessageList[i->GetPriority()].empty())
		{
			lNotEmpty = true;
			i->ReciveMessage(mAgentMessageList[i->GetPriority()][0]);
		}
	}
	return lNotEmpty;
}

int CEntityManager::GetNumAgents()
{
	return mAgentList.size();
}

std::vector<CAgent*>* CEntityManager::GetAgentList()
{
	return &mAgentList;
}
