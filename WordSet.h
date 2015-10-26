#pragma once
#include <vector>
#include <iterator>

class WordSet
{
public:
	struct MarkedWord
	{
		bool		alive = true;
		std::string	word;
		MarkedWord(std::string word_) : word(word_) {};
	};

private:
	std::vector<MarkedWord> words;

	int targetSize = 0;

	std::vector<char> knowns; // known characters in the word, 0 = unknown
	std::vector<char> unuseds; // characters the target word does not have

public:
	void	add_word(std::string word); // add a word to the potential word list

	void	reset(); // mark all words as alive and reset the board
	size_t	set_known(char letter, int place); // set a character as known to be in this position
	size_t	set_unused(char letter); // mark a letter as not appearing in this target word
	size_t	set_targetSize(int n); // set the size of the word we're searching for.

	size_t	potential_wordcount() const; // see how many potential words are marked alive

	std::vector<char> get_knowns() const; // get known characters
	std::vector<char> get_unused() const; // get characters known to be unused

	WordSet();
	~WordSet();

	std::vector<MarkedWord>::iterator begin();
	std::vector<MarkedWord>::iterator end();
	std::vector<MarkedWord>::const_iterator begin() const;
	std::vector<MarkedWord>::const_iterator end() const;
};

