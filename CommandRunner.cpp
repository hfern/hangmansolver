#include "CommandRunner.h"
#include <sstream>

using namespace std;

CommandRunner::CommandRunner(std::istream& in, std::ostream& out, WordSet& wordset_): 
	ioh(in, out), wordset(wordset_)
{
}


CommandRunner::~CommandRunner()
{
}

void CommandRunner::Run()
{
	string line;

	ioh.out << "Playing hangman...\n"
			<< "Maybe try \"help\"\n";


	while (true)
	{
		ioh.out << "~ ";

		getline(cin, line);
		istringstream ss(line);

		string commandName;
		ss >> commandName;

		if (!ss)
		{
			// not able to read command name, so blank line
			continue;
		}

		if (commands.find(commandName) == commands.end())
		{
			ioh.out << "No such command \"" << commandName << "\"\n";
			continue;
		}

		string restline;
		getline(ss, restline);

		commands[commandName]->call(wordset, restline);
	}
}

const CommandRunner::CommandMap* CommandRunner::Commands() const
{
	return &commands;
}

std::string CommandRunner::getPrompt() const
{
	return prompt;
}