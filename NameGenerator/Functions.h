#pragma once
#include "Defines.h"

#pragma region Functions
/// <summary>
/// Generates a random double between 0 and 1
/// </summary>
/// <returns>A random double between 0 and 1</returns>
double RandomDouble()
{
	return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}

/// <summary>
/// Reads the input file and puts all the names into the Names vector
/// </summary>
/// <param name="FileName">The name of the file that will be read to 
///                        generate the probabilites of the letter combinations</param>
void ReadFile(std::string FileName)
{
	char currLine[128];
	FileToRead.open(FileName);
	if (FileToRead.is_open())
	{
		while (!FileToRead.eof())
		{
			FileToRead.getline(currLine, 128);
			Names.push_back(currLine);
		}
		FileToRead.close();
	}
}

/// <summary>
/// Gets the lengths of the longest name and the shortest name and saves
/// them in the Max_Characters and Min_Characters variables respectively 
/// </summary>
void MinMax()
{
	MaxCharacters = Names[0].size();
	MinCharacters = Names[0].size();
	for (auto name : Names)
	{
		if (name.size() > MaxCharacters)
		{
			MaxCharacters = name.size();
		}
		if (name.size() < MinCharacters && name.size() != 0)
		{
			MinCharacters = name.size();
		}
	}
}

/// <summary>
/// Fills the Data feild's Alphabet variable with all 26 letters of the alphabet and whether each letter is a consonant, vowel, or both
/// </summary>
void InitData()
{
	for (int i = 0; i < 26; i++)
	{
		Data.Alphabet[i].Lower = (char)(i + 97);
		Data.Alphabet[i].Upper = (char)(i + 65);

		if (i == 0 || i == 4 || i == 8 || i == 14 || i == 20) //a,e,i,o,u
		{
			Data.Alphabet[i].isConsonant = false;
			Data.Alphabet[i].isVowel = true;
		}
		else if (i == 24) //y
		{
			Data.Alphabet[i].isConsonant = true;
			Data.Alphabet[i].isVowel = true;
		}
		else //all other letters
		{
			Data.Alphabet[i].isConsonant = true;
			Data.Alphabet[i].isVowel = false;
		}
	}
}

/// <summary>
/// Searches the Data field's Combo vector to see if a letter combination exists
/// </summary>
/// <param name="combo">The letter combination being looked for</param>
/// <returns>The place in the vector if the combination is found and -1 if not</returns>
int FindCombination(std::string combo)
{
	for (int i = 0; i < Data.Combos.size(); i++)
	{
		if (combo == Data.Combos[i].Combo)
		{
			return i;
		}
	}
	return -1;
}

/// <summary>
/// Calculates all of the letter combination probabilities, given a list of names
/// and them sorts all of the combos in alphabetical order
/// </summary>
void GenerateProb()
{
	std::string combo = "";
	for (auto name : Names)
	{
		for (int i = 0; i < name.size(); i++)
		{
			if (i + 1 < name.size())
			{
				
				combo += toupper(name[i]);
				combo += toupper(name[i + 1]);
				if (FindCombination(combo) == -1)
				{
					Data.Combos.push_back({ combo, 1.0 });
				}
				else
				{
					Data.Combos[FindCombination(combo)].Prob += 1.0;
				}
				combo = "";
			}
		}
	}

	std::sort(Data.Combos.begin(), Data.Combos.end(), Comparator);
}

/// <summary>
/// Takes the probalilities of all of the combinations and normalizes them based on
/// what the first character in the combination is
/// </summary>
void NormalizeProb()
{
	char firstLetter;
	int letterCount = 0;
	for (int i = 0; i < 26; i++)
	{
		firstLetter = (char)(i + 65);
		for (auto combo : Data.Combos)
		{
			if (combo.Combo[0] == firstLetter)
			{
				letterCount += combo.Prob;
			}
		}

		if (letterCount > 0)
		{
			for (int i = 0; i < Data.Combos.size(); i++)
			{
				if (Data.Combos[i].Combo[0] == firstLetter)
				{
					Data.Combos[i].Prob = Data.Combos[i].Prob / (double)letterCount;
				}
			}
		}
		letterCount = 0;
	}
}

char PickLetter(int prevLetter)
{
	std::vector<COMBOPROB> Combos;
	char firstLetter = (char)(prevLetter + 65);
	double total = RandomDouble();

	//Creates a vector containing all combinations that start with prevLetter
	for (auto combo : Data.Combos)
	{
		if (combo.Combo[0] == firstLetter)
		{
			Combos.push_back(combo);
		}
	}

	//Goes through all of the combinations in the Combos vector
	for (int i = 0; i < Combos.size(); i++)
	{
		//if the probability of Combos[i] is <= the total, return the second letter in the combo
		if (Combos[i].Prob <= total)
		{
			return Combos[i].Combo[1];
		}
		//else, add the total 
		else
		{
			total += Combos[i].Prob;
		}
	}
	return '!';
}

CHARACTER GetLetter(int letter, bool consonant, bool vowel)
{
	
	CHARACTER randLetter;
	bool loop = true;
	while (loop)
	{
		randLetter = Data.Alphabet[rand() % 25];
		if ((consonant && randLetter.isConsonant) || (vowel && randLetter.isVowel))
		{
			loop = true;
		}
		else
		{
			return randLetter;
		}
	}
}

/// <summary>
/// Generates a random name based on the caculated probabilities
/// </summary>
/// <param name="min">The minimum number of characters in the name</param>
/// <param name="max">The maximum number of characters in the name</param>
/// <returns>The generated name</returns>
std::string GenerateName(int min = 0, int max = 0)
{
	if (min == 0)
	{
		min = MinCharacters;
	}
	if (max == 0)
	{
		max = MaxCharacters;
	}
	int currLetter;
	int prevLetter = 0;
	int nameLength = rand() % min + max;
	std::string name;
	bool isPrevC = false; //was the previous letter a consonant
	bool isPrevC2 = false;//were the previous 2 letters consonants
	bool isPrevV = false; //was the previous letter a vowel
	bool isPrevV2 = false;//were the previous 2 letters vowels

	for (int i = 0; i < nameLength; i++)
	{
		if (i == 0)
		{
			currLetter = rand() % 25;
			name += Data.Alphabet[currLetter].Upper;
		}
		else
		{
			currLetter = (int)PickLetter(prevLetter);
			name += Data.Alphabet[currLetter].Lower;
		}

		isPrevC2 = Data.Alphabet[currLetter].isConsonant && isPrevC;
		isPrevV2 = Data.Alphabet[currLetter].isVowel && isPrevV;
		isPrevC =  Data.Alphabet[currLetter].isConsonant;
		isPrevV =  Data.Alphabet[currLetter].isVowel;
		prevLetter = currLetter;
	}
	return name;
}
#pragma endregion

#pragma region Tests
/// <summary>
/// Test to see if the Data feild's Alphabet variable is filled with all of the correct information
/// </summary>
void InitData_Test()
{
	for (int i = 0; i < 26; i++)
	{
		std::cout << Data.Alphabet[i].isConsonant << " " << Data.Alphabet[i].isVowel << " "
			      << Data.Alphabet[i].Lower << " " << Data.Alphabet[i].Upper << std::endl;
	}
}

/// <summary>
/// Test to see if the names that are read and placed into the Names vector
/// </summary>
void ReadFile_Test()
{
	for (auto name : Names)
	{
		std::cout << name << std::endl;
	}
}

/// <summary>
/// Test to see if the probabilities are properly calculated
/// </summary>
void GenerateProb_Test()
{

	
	char firstLetter;
	int letterCount = 0;
	for (int i = 0; i < 26; i++)
	{
		firstLetter = (char)(i + 65);
		for (auto combo : Data.Combos)
		{
			if (combo.Combo[0] == firstLetter)
			{
				std::cout << combo.Combo << ": " << combo.Prob << " ";
			}
		}
		std::cout << "\n---------------------------------------------------------\n";
	}
	
	/*
	
	for (auto prob : Data.Combos)
	{
		std::cout << prob.Combo << " " << prob.Prob << std::endl;
	}
	*/
	
}
#pragma endregion

