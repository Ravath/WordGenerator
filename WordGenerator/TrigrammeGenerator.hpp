#ifndef TRIGRAMME_GENERATOR_H
#define TRIGRAMME_GENERATOR_H

#include <map>

#include "AbsWorldGenerator.hpp"

class TrigrammeGenerator : public AbsWordGenerator
{
public:
	TrigrammeGenerator(unsigned int sequenceSize );
	~TrigrammeGenerator() = default;

	void AddWord(std::string const&word);
	std::string ComputeWord(unsigned int length);
	std::string ComputeWord();
	std::string ComputeWordWithUnsetLength();
	unsigned int GetRandomLength();
	bool UnmanagedCharacter(unsigned char c);
	void FormatWord(std::string & index);

private:
	unsigned int _gramSize;//nombre max de caractères consécutifs à considérer pour calculer les probabilitée des séquences.
	std::map<std::string,unsigned int[257]> _occurences;//à une squence de charactère, associe les chances de la lettre suivante. l'indice 256 est la somme des occurences
	unsigned int _nbrWords;
	std::map<unsigned int, unsigned int> _lengths;

	unsigned char getLetter(std::string const& index);
	bool canContinue(std::string const& gram);
	void addOccurence(std::string const& index, unsigned char letter);
	unsigned int getNbrOcc(std::string const& index);
	void addNbrOcc(std::string const& index);
};

#endif

