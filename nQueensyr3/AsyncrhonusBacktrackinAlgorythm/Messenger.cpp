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
	newMessage.Message.UID = to;
	newMessage.Message.Value = message;
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
		return mMessageList[0];
		mMessageList.pop_front();
	}
	SMessage Empty;
	Empty.UIDto = -1;
	return Empty;
}
