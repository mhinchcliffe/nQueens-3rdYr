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

public:
	CMessenger();
	~CMessenger();
};

