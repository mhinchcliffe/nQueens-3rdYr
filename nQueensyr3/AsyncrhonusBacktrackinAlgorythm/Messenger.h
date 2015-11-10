#pragma once
#include "Common.h"
enum eMessageType 
{
	Ok,
	NoGood,
};
struct SMessage 
{
	int UIDto;
	int UIDfrom;
	eMessageType Type;
	SAgentV Message;
};

class CMessenger
{
	std::deque<SMessage> mMessageList;

public:
	CMessenger();
	~CMessenger();

	void AddMessage(SMessage newMessage);
	void AddMessage(int to, int from, eMessageType type, int message);
	void ClearMessageList();
	bool IsMessgeListEmpty();
	SMessage GetNextMessage();
};

