#include "WordSet.h"

void WordSet::add_word(std::string word)
{
	words.push_back(MarkedWord(word));
}

void WordSet::reset()
{
	for (MarkedWord& word: words)
	{
		word.alive = true;
	}
	targetSize = 0;
	knowns = {};
	unuseds = {};
}

size_t WordSet::set_known(char letter, int place)
{
	size_t	killed = 0;
	knowns[place] = letter;

	for (MarkedWord& word : words)
	{
		if (word.alive && word.word[place] != letter)
		{
			killed++;
			word.alive = false;
		}
	}

	return killed;
}

size_t WordSet::set_unused(char letter)
{
	size_t	killed = 0;
	unuseds.push_back(letter);

	for (MarkedWord& word : words)
	{
		if (word.alive)
		{
			for (char hasLetter : word.word)
			{
				if (letter == hasLetter)
				{
					word.alive = false;
					killed++;
					continue;
				}
			}
		}
	}

	return killed;
}

size_t WordSet::set_targetSize(int n)
{
	targetSize = n;
	size_t	killed = 0;

	knowns.reserve(n);
	for (int i = knowns.size(); i < n; i++)
	{
		knowns.push_back('\0');
	}

	for (MarkedWord& word: words)
	{
		if (word.word.length() != n && word.alive)
		{
			word.alive = false;
			killed++;
		}
	}

	return killed;
}

size_t WordSet::potential_wordcount() const
{
	size_t count = 0;

	for(auto& word: words)
	{
		if (word.alive) count++;
	}

	return count;
}

std::vector<char> WordSet::get_knowns() const
{
	return knowns;
}

std::vector<char> WordSet::get_unused() const
{
	return unuseds;
}

WordSet::WordSet()
{
}


WordSet::~WordSet()
{
}

std::vector<WordSet::MarkedWord>::iterator WordSet::begin()
{
	return words.begin();
}

std::vector<WordSet::MarkedWord>::iterator WordSet::end()
{
	return words.end();
}

std::vector<WordSet::MarkedWord>::const_iterator WordSet::begin() const
{
	return words.begin();
}

std::vector<WordSet::MarkedWord>::const_iterator WordSet::end() const
{
	return words.end();
}