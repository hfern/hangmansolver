
#include <iostream>
#include "letter.h"
#include <fstream>
#include "WordSet.h"
#include "CommandRunner.h"
#include "stdcommands.h"

using namespace std;

void load(string filename, WordSet& wordset)
{
	ifstream file(filename);
	string word;

	file >> word;
	while(file)
	{
		wordset.add_word(word);
		file >> word;
	}
}

int main()
{
	
	WordSet wordset;

	cout << "loading...\n";
	load("words.txt", wordset);
	cout << "done loading...\n";

	CommandRunner cr(cin, cout, wordset);

	cr.RegisterCommand<Commands::SetLength>("length");
	cr.RegisterCommand<Commands::SetCharacter>("char");
	cr.RegisterCommand<Commands::SetNo>("no");
	cr.RegisterCommand<Commands::Words>("words");
	cr.RegisterCommand<Commands::Help>("help");
	cr.RegisterCommand<Commands::Count>("count");
	cr.RegisterCommand<Commands::Reset>("reset");
	cr.RegisterCommand<Commands::Analyze>("analyze");
	cr.RegisterCommand<Commands::Clear>("clear");

	cr.Run();

	return 0;
}