#include <time.h>
#include <assert.h>
#include <iostream>

#include "TrigrammeGenerator.hpp"

using namespace std;

TrigrammeGenerator::TrigrammeGenerator(unsigned int sequenceSize) : AbsWordGenerator()
{
	if (sequenceSize < 2)
		throw exception("sequenceSize must be equal or greater than 2");
	_gramSize = sequenceSize;
	srand((unsigned int)time(NULL));
}

void TrigrammeGenerator::AddWord(string const & word)
{
	if (word.length() < 1)
		return;
	_nbrWords++;
	_lengths[word.length()]++;

	//début du mot
	string s = " ";
	addOccurence(s, word[0]);
	for (size_t i = 0; i < _gramSize -1 && i < word.length() ; i++)//_gramSize-1 because already ' '
	{
		s += word[i];
		addOccurence(s, word[i+1]);
	}

	//milieu du mot
	for (size_t i = 0; (i + _gramSize) <= word.length(); i++)
	{
		string index = word.substr(i, _gramSize);
		if (i + _gramSize == word.length()) {//fin du mot
			addOccurence(index, ' ');
		}
		else {//milieu de mot
			addOccurence(index, word[i + _gramSize]);
		}
	}

	//word end : particular case if word too small
	if (word.length() < _gramSize) {
		addOccurence(word, ' ');
	}
}

string TrigrammeGenerator::ComputeWord(unsigned int length)
{
	string ret;
	ret += getLetter(" ");
	for (size_t i = 0; i < length - 1; i++)
	{
		string index;
		if (_gramSize - 2 > i) {//-1 pour espace et -1 pour lettre à trouver
			index = " " + ret;
		}
		else {
			index = ret.substr(ret.length() - _gramSize + 1);
		}
		if (canContinue(index))
			ret += getLetter(index);
		else
			return ret;
	}


	return ret;
}

string TrigrammeGenerator::ComputeWord()
{
	return AbsWordGenerator::ComputeWord();
}

string TrigrammeGenerator::ComputeWordWithUnsetLength()
{
	unsigned int i = 0;
	char newLetter;
	string ret = "";

	//première lettre
	ret += getLetter(" ");

	do {
		newLetter = getLetter(" " + ret);
		ret += newLetter;
		i++;

		//(i+1) pour compter l'espace
	} while (newLetter != ' ' && (i+1) < _gramSize);

	//lettres du milieu
	i = 0;
	do {
		string index;

		index = ret.substr(ret.length() - _gramSize);
		newLetter = getLetter(index);
		ret += newLetter;
		i++;
	} while (newLetter != ' ');// continuer jusqu'à fin de mot

	return ret;
}

unsigned int TrigrammeGenerator::GetRandomLength()
{
	unsigned int rd = rand() % _nbrWords;
	for each (auto l in _lengths)
	{
		if (rd < l.second)
			return l.first;
		rd -= l.second;
	}
	assert(false);
	return 5;
}

void TrigrammeGenerator::FormatWord(string & index)
{
	for (size_t i = 0; i < index.length(); i++)
	{
		if (index[i] >= 'A' && index[i] <= 'Z')
			index[i] += 'a' - 'A';
	}
}

unsigned char TrigrammeGenerator::getLetter(string const& index) {
	unsigned int max = getNbrOcc(index);
	unsigned int rd = rand() % max;

	for (unsigned char i = 0; i < 257; i++)
	{
		if (rd < _occurences[index][i]) {
			return (unsigned char)i;
		}
		rd -= _occurences[index][i];
	}
	assert(false);
	return 'a';
}

inline bool TrigrammeGenerator::canContinue(string const& gram)
{
	return _occurences.find(gram) != _occurences.end() && getNbrOcc(gram) != 0;
}

inline void TrigrammeGenerator::addOccurence(string const & index, unsigned char letter)
{
	_occurences[index][letter]++;
	addNbrOcc(index);
}

bool TrigrammeGenerator::UnmanagedCharacter(unsigned char c)
{
	return c <'a';
}

inline unsigned int TrigrammeGenerator::getNbrOcc(string const& index) {
	return _occurences[index][256];
}
inline void TrigrammeGenerator::addNbrOcc(string const& index) {
	_occurences[index][256]++;
}
