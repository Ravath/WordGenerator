#include "WordGenerator.hpp"

#include <random>
#include <time.h>
#include <map>

using namespace std;

WordGenerator::WordGenerator() : AbsWordGenerator()
{
	memset(_occMat, 0, 27*27);
	memset(_occRow, 0, 27);
	/* initialize random seed: */
	srand ((unsigned int)time(NULL));
}

void WordGenerator::AddWord(string const& w)
{
	//pas de mots vides
	if (w.length() < 1)
		return;
	//enregistrer longeurs
	_nbrMots++;
	_lengths[w.length()]++;
	//init
	char let = w[0];
	addOccurence(' ', let);
	//milieu du mot
	for (size_t i = 1; i < w.length(); i++)
	{
		char nl = w[i];
		addOccurence(let, nl);
		let = nl;
	}
	//dernière lettre
	addOccurence(let, ' ');
}
//todo : redresser si ne trouve pas de lettre finale.
string WordGenerator::ComputeWord(unsigned int length)
{
	if (length <= 0)
		return string("");
	char *word = new char[length+1];
	word[length] = '\0';
	//première lettre
	do {
		word[0] = getLetter(' ');
	} while (!canContinue(word[0]));
	if(length==1)
		return string(word);
	//lettre du milieu
	unsigned int i = 1;
	while (i < length-1) {
		do {
			word[i] = getLetter(word[i - 1]);
		} while (!canContinue(word[i]));
		i++;
	}
	//dernière lettre
	do {
		word[i] = getLetter(word[i - 1]);
	} while (!canFinish(word[i]));
	return string(word);
}

string WordGenerator::ComputeWord()
{
	return AbsWordGenerator::ComputeWord();
}

unsigned int WordGenerator::GetRandomLength()
{
	unsigned int rd = rand() % _nbrMots;
	for each (auto l in _lengths)
	{
		if (rd < l.second)
			return l.first;
		rd -= l.second;
	}
	assert(false);
	return 5;
}

bool WordGenerator::UnmanagedCharacter(unsigned char c)
{
	return charToIndex(c)==-1;
}

void WordGenerator::addOccurence(char firstLetter, char nextLetter)
{
	int i = charToIndex(firstLetter);
	int j = charToIndex(nextLetter);
	assert(i >= 0 && i<=26);
	assert(j >= 0 && j <= 26);
	//if (j != 26) {
		_occRow[i]++;
		_occMat[i][j]++;
		_nbrOcc++;
	//}
}

int WordGenerator::charToIndex(short letter)
{
	if (letter >= 'A' && letter <= 'Z') {
		return letter - 'A';
	}
	else if (letter >= 'a' && letter <= 'z') {
		return letter - 'a';
	}
	else if (letter == ' ') {
		return 26;
	}
	else {
		return -1;
		//switch (letter)
		//{
		//case 'é':
		////case 'è':
		////case 'ê':
		//	return 'e' - 'a';
		//case 'ô':
		////case '・:
		//	return 'o' - 'a';
		//case 'â':
		////case '・:
		////case '・:
		//	return 'a' - 'a';
		//case 'û':
		////case '・:
		////case '・:
		//	return 'u' - 'a';
		//case 'î':
		////case '・:
		//	return 'i' - 'a';
		//default:
		//	return -1;
		//}
	}
}

char WordGenerator::getLetter(char prevletter)
{
	//get index of letter
	int ci = charToIndex(prevletter);
	assert(ci >= 0 && ci <= 26);
	//draw random number
	double f = (double)rand() / RAND_MAX;//valeur aléatoire entre 0 et 100
	//get desiged letter
	for (unsigned char i = 0; i < 26; i++)//parcourir la lige pour les valeurs de 'a' ・'z'
	{
		double odd = (double)_occMat[ci][i] / (double)(_occRow[ci] - _occMat[ci][26]);//enlever les chances de trouver un espace
		if (f < odd + 1E-10)
			return 'a' + i;
		f -= odd;
	}
	assert(false);
	return 0;
}

bool WordGenerator::canContinue(char letter)
{
	int i = charToIndex(letter);
	assert(i >= 0 && i <= 26);
	return _occRow[i] != 0;
}

bool WordGenerator::canFinish(char lastLetter)
{
	int i = charToIndex(lastLetter);
	assert(i >= 0 && i <= 26);
	return _occMat[i][26] > 0;
}
