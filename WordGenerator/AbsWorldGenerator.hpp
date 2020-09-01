#pragma once

//#ifndef ABS_WORD_GENERATOR_H
//#define ABS_WORD_GENERATOR_H

#include <string>
#include <list>
#include <vector>
#include <forward_list>

class AbsWordGenerator
{
public:
	AbsWordGenerator() = default;
	~AbsWordGenerator() = default;

	void AddWords(std::list<std::string> const& words);
	void AddWords(std::vector<std::string> const& words);
	void AddWords(std::forward_list<std::string> const& words);
	virtual void AddWord(std::string const&word) = 0;
	virtual std::string ComputeWord(unsigned int length) = 0;
	virtual std::string ComputeWord() = 0;
	virtual unsigned int GetRandomLength() = 0;
	virtual bool UnmanagedCharacter(unsigned char c) = 0;

};

//#endif