#ifndef WORD_GENERATOR_H
#define WORD_GENERATOR_H

#include <string>
#include <vector>
#include <cassert>
#include <list>
#include <iterator>
#include <forward_list>
#include <map>

#include "AbsWorldGenerator.hpp"

using namespace std;

class WordGenerator : public AbsWordGenerator
{
public:
	WordGenerator();
	~WordGenerator() = default;

	void AddWord(string const& word);
	string ComputeWord(unsigned int length);
	string ComputeWord();
	unsigned int GetRandomLength();
	bool UnmanagedCharacter(unsigned char c);

private:
	unsigned int _occMat[27][27];//compte le nombre de fois qu'une occurence se produit
	unsigned int _occRow[27];
	map<unsigned int, unsigned int> _lengths;//<longueur, nbr occurences
	unsigned int _nbrOcc = 0;//nombre d'occurences
	unsigned int _nbrMots = 0;//nombre d'occurences


	void addOccurence(char firstLetter, char nextLetter);
	int charToIndex(short letter);
	//returns a letter picked randomly from the matrice
	char getLetter(char prevletter);
	//returns true if the letter can be at the end of a word.
	bool canFinish(char lastLetter);
	//return true if the letter can be foloowed by at least one other.
	bool canContinue(char letter);
};

#endif
