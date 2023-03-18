#include "Functions.h"

int main()
{
#if 1
	InitData();
	ReadFile("HumanMale.txt");
	MinMax();
	GenerateProb();
	NormalizeProb();
#endif // 0

	
#if 1
	//InitData_Test();
	//ReadFile_Test();
	GenerateProb_Test();
#endif // 0

	//std::cout << GenerateName(5, 10);
}

//Credit to the YouTube Channel Let's Code Physics for the tutorial followed to make the code
//Link: https://www.youtube.com/channel/UCWBTKIyw-zX-2k63cB6qciQ

//Credit to https://www.fantasynamegenerators.com/ for all of the names used to generate probabilities