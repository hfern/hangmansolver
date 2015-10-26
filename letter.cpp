#include "letter.h"
#include <tuple>
#include <sstream>

using namespace std;


bool LetterNode::is_lastchar()
{
	return following.count('\0') != 1;
}

LetterNode::LetterNode()
{
}

LetterNode::LetterNode(char letter_, LetterNode* parent_): letter(letter_), parent(parent_)
{
}

LetterNode::~LetterNode()
{
}

void LetterTree::insert(std::string word)
{
	using KeyType = std::pair<char, LetterNode>;

	LetterNode* currentNode = this;
	LetterMap* nextmap = &following;

	for(char c : word)
	{
		if (!nextmap->count(c))
		{
			auto ln = LetterNode(c, currentNode);
			nextmap->insert(KeyType(c, ln));
		}

		currentNode = &nextmap->at(c);
		nextmap = &currentNode->following;
	}
	nextmap->insert(KeyType('\0', EOW));
}

LetterTree::LetterTree(): EOW(LetterNode('\0'))
{
}

LetterTree::iterstate LetterTree::search(std::string term)
{
	iterstate iter;
	iter.root = this;
	iter.term = term;
	iter.stack.push_back(this);
	return iter;
}

void pretty_print(std::ostream& os, const LetterTree& t)
{
	for (const auto& kv: t.following)
	{
		pretty_print(os, kv.second, 0);
	}
}

void pretty_print(std::ostream& os, const LetterNode& letter, int indentLevel)
{
	std::string indentWS(indentLevel*2, ' ');
	os << indentWS << "-" << letter.letter;

	const LetterNode* lptr = &letter;

	while(lptr->following.size() == 1)
	{
		LetterNode::LetterMap::const_iterator nextIt = lptr->following.begin();
		const LetterNode& nextNode = (*nextIt).second;
		os << nextNode.letter;
		lptr = &nextNode;
	}

	os << "\n";

	for (const auto& kv : lptr->following)
	{
		pretty_print(os, kv.second, indentLevel + 2);
	}
	
}

void parse_wordlist(std::istream& list, LetterTree& words)
{
	string word;

	list >> word;
	while (list)
	{
		words.insert(word);
		list >> word;
	}
}

void LetterTree::iterstate::iter()
{

}