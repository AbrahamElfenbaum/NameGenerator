#include "Functions.h"

int main()
{
    InitData();
	//InitData_Test();
	ReadFile("HumanMale.txt");
	MinMax();
	//ReadFile_Test();
	GenerateProb();
	NormalizeProb();
	//GenerateProb_Test();
	std::cout << GenerateName(5, 10);
}

//Credit to the YouTube Channel Let's Code Physics for the tutorial followed to make the code
//Link: https://www.youtube.com/channel/UCWBTKIyw-zX-2k63cB6qciQ

//Credit to https://www.fantasynamegenerators.com/ for all of the names used to generate probabilities