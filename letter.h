#pragma once

#include <map>
#include <string>
#include <ostream>
#include <vector>


class LetterNode
{
	LetterNode* parent;
public:
	using LetterMap = std::map<char, LetterNode>;

	char letter;
	LetterMap following;

	bool is_lastchar();

	LetterNode();
	explicit LetterNode(char letter_, LetterNode* parent_ = nullptr);
	~LetterNode();
};


// Root node of a letter map
class LetterTree: public LetterNode
{
public:
	const LetterNode EOW; // the end of word node 

	// Add a word to the dictionary
	void insert(std::string word);

	LetterTree();

	class iterstate
	{
		friend class LetterTree;

		// Has the search reached the end state? / the yielded value ("" when done)
		using result_t = std::pair<bool, std::string>;

		std::string					term; // term we're searching for
		int							termptr;
		std::vector<const LetterNode*>	stack; // stack of character's we're at

		bool 						done = false;
		const LetterTree*			root;

		void iter();
	};
public:
	iterstate	search(std::string);
};

void pretty_print(std::ostream&, const LetterTree&);
void pretty_print(std::ostream&, const LetterNode&, int level = 0);

void parse_wordlist(std::istream&, LetterTree&);

std::vector<const LetterNode*> get_matches(const LetterTree& root, std::string term);

//LetterTree deserialize_tree()