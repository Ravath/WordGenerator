#include "AbsWorldGenerator.hpp"

void AbsWordGenerator::AddWords(std::list<std::string> const & words)
{
	for each (std::string s in words)
	{
		AddWord(s);
	}
}
void AbsWordGenerator::AddWords(std::vector<std::string> const & words)
{
	for each (std::string s in words)
	{
		AddWord(s);
	}
}
void AbsWordGenerator::AddWords(std::forward_list<std::string> const & words)
{
	for each (std::string s in words)
	{
		AddWord(s);
	}
}

std::string AbsWordGenerator::ComputeWord()
{
	return ComputeWord(GetRandomLength());
}