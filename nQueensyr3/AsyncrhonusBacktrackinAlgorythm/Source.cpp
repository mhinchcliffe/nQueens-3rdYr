#include "AsyncBackTrackAlg.h"
#include "Common.h"

int main()
{
	CEntityManager* FourQueensProblem = new CEntityManager(4);
	CAsyncBackTrackAlg NewInstance(FourQueensProblem);
	std::cout << "hey"<<std::endl;
	system("pause");
}