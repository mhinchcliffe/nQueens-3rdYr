#include "AsyncBackTrackAlg.h"
#include "Common.h"

int main()
{
	CEntityManager* FourQueensProblem = new CEntityManager(4);
	CAsyncBackTrackAlg NewInstance(FourQueensProblem);
	for (int i = 0; i < 10; i++)
	{
		std::cout << "//- PASS " << i << " -//" << std::endl;
		NewInstance.Update();
		NewInstance.PrintSolution();
	}


	std::cout << "hey"<<std::endl;
	system("pause");
}