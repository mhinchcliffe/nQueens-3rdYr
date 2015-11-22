#include "Messenger.h"



CMessenger::CMessenger()
{
}


CMessenger::~CMessenger()
{
}

void CMessenger::AddMessage(SMessage newMessage)
{
	mMessageList.push_back(newMessage);
}

void CMessenger::AddMessage(int to, int from, eMessageType type, int message)
{
	SMessage newMessage;
	newMessage.UIDto = to;
	newMessage.UIDfrom = from;
	newMessage.Type = type;
	newMessage.Message.UID = from;
	newMessage.Message.Value = message;
	mMessageList.push_back(newMessage);
}

void CMessenger::ClearMessageList()
{
	mMessageList.clear();
}

bool CMessenger::IsMessgeListEmpty()
{
	if (mMessageList.size() == 0)
	{
		return true;
	}
	else return false;
}

SMessage CMessenger::GetNextMessage()
{
	if (!IsMessgeListEmpty())
	{
		SMessage temp= mMessageList[0];
		mMessageList.pop_front();
		return temp;
	}
	SMessage Empty;
	Empty.UIDto = -1;
	return Empty;
}
