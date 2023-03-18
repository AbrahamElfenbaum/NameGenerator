#pragma once
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
//#include <ctype.h>
#include <algorithm>

struct CHARACTER
{
	char Lower, Upper;
	bool isConsonant, isVowel;
};

struct COMBOPROB
{
	std::string Combo;
	double Prob;
};

struct DATA
{
	CHARACTER Alphabet[26];
	std::vector<COMBOPROB> Combos;
};

struct COMPARATOR
{
	bool operator()(COMBOPROB obj1, COMBOPROB obj2)
	{
		return obj1.Combo < obj2.Combo;
	}
} Comparator;

DATA Data;
std::ifstream FileToRead;
std::vector<std::string> Names;
int MinCharacters;
int MaxCharacters;