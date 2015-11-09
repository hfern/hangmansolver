#pragma once
#include "WordSet.h"
#include <vector>

class Analyzer
{
	WordSet& wordset;
public:
	struct LetterFrequencyEntry
	{
		char	letter;
		size_t	frequency;
		float	relfreq;
	};

	std::vector<LetterFrequencyEntry> getLetterFrequencies() const;

	Analyzer(WordSet& ws): wordset(ws) {};
	~Analyzer();
};

