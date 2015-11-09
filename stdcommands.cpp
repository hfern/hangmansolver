#include "stdcommands.h"
#include "CommandRunner.h"
#include <iomanip>
#include <map>
#include <vector>
#include "Analyzer.h"
#include <algorithm>

using namespace std;

std::pair<std::string, std::string> Commands::SetLength::helptext() const
{
	return {"LENGTH", "Set the length of the target word."};
}

void Commands::SetLength::call(WordSet& wordset, std::string args)
{
	args = trim(args);
	istringstream ss(args);

	int length;
	ss >> length; 

	size_t killed = wordset.set_targetSize(length);
	io.out << "Eliminated " << killed << " potential words.\n";
}

std::pair<std::string, std::string> Commands::SetCharacter::helptext() const
{
	return {
		"POSITION CHARACTER",
		"Filter to words only containing CHARACTER at POSITION in the word."
	};
}

void Commands::SetCharacter::call(WordSet& wordset, std::string args)
{
	args = trim(args);
	istringstream ss(args);

	int position;
	char character;

	ss >> position >> character;

	size_t killed = wordset.set_known(character, position);
	io.out << "Eliminated " << killed << " potential words.\n";
}

std::pair<std::string, std::string> Commands::SetNo::helptext() const
{
	return {
		"CHARACTER",
		"Remove any words containing this character from the word list."
	};
}

void Commands::SetNo::call(WordSet& wordset, std::string args)
{
	args = trim(args);
	istringstream ss(args);

	char character;
	ss >> character;

	size_t killed = wordset.set_unused(character);
	io.out << "Eliminated " << killed << " potential words.\n";
}

std::pair<std::string, std::string> Commands::Words::helptext() const
{
	return {
		"",
		"Print potential words"
	};
}

void Commands::Words::call(WordSet& wordset, std::string args)
{
	size_t count = wordset.potential_wordcount();
	if (count > 100)
	{
		io.out << "There are " << count << " potential words.\n";
		io.out << "Are you sure you want to print them all (Y/n)? ";

		char answer;
		io.in >> answer;
		if (!(answer == 'Y' || answer == 'y'))
		{
			return;
		}
	}

	for (auto it = wordset.begin(); it != wordset.end(); ++it)
	{
		if ((*it).alive)
		{
			io.out << " * " << (*it).word << "\n";
		}
	}
}

std::pair<std::string, std::string> Commands::Help::helptext() const
{
	return {
		"",
		"List all commands."
	};
}

void Commands::Help::call(WordSet& wordset, std::string args)
{
	using CVT = CommandRunner::CommandMap::value_type;
	io.out << "The following commands are available:\n";


	int largestSize = 0;

	for (CVT comm: *runner->Commands())
	{
		if (comm.first.size() > largestSize)
		{
			largestSize = comm.first.size();
		}
	}

	for (CVT comm : *runner->Commands())
	{

		cout << setw(largestSize) << comm.first << " \t" << comm.second->helptext().first << "\n";
		cout << setw(largestSize) << " " << " \t" << comm.second->helptext().second << "\n";
	}
}

std::pair<std::string, std::string> Commands::Count::helptext() const
{
	return {
		"",
		"List the count of remaining potential words."
	};
}

void Commands::Count::call(WordSet& wordset, std::string args)
{
	io.out << "There are " << wordset.potential_wordcount()
		<< " potential words remaining.\n";
}

std::pair<std::string, std::string> Commands::Reset::helptext() const
{
	return{
		"",
		"Reset the game. Deletes all progress data :("
	};
}

void Commands::Reset::call(WordSet& wordset, std::string args)
{
	io.out << "Are you sure you want to reset? Type \"yes\" if so: ";
	string answer;
	io.in >> answer;

	if (answer == "yes")
	{
		wordset.reset();
	}
	else
	{
		io.out << "NOT resetting.\n";
	}

}

std::pair<std::string, std::string> Commands::Analyze::helptext() const
{
	return{ "", "Analyze all potential words for letter frequencies." };
}

void Commands::Analyze::call(WordSet& wordset, std::string args)
{
	Analyzer analyzer(wordset);
	auto frequencies = analyzer.getLetterFrequencies();

	vector<char> dontShow = wordset.get_knowns();
	vector<char> unuseds = wordset.get_unused();
	dontShow.insert(dontShow.end(), unuseds.begin(), unuseds.end());

	auto n = wordset.potential_wordcount();

	io.out << "Letter \t Frequency \t RFreq.\n";
	for (auto kt: frequencies)
	{
		bool skip = false;

		for (auto letter: dontShow)
		{
			if (kt.letter == letter)
			{
				skip = true;
				break;
			}
		}

		if (skip)
		{
			continue;
		}

		io.out << "  " << kt.letter << "   \t " << setw(9) << kt.frequency << " \t ";
		if (n == 0)
		{
			io.out << "  -  ";
		}
		else
		{
			io.out << fixed << setprecision(3) << kt.relfreq;
		}

		io.out << "\n";
	}
}

std::pair<std::string, std::string> Commands::Clear::helptext() const
{
	return {"", "Clear the console."};
}

void Commands::Clear::call(WordSet& wordset, std::string args)
{
	string prompt = runner->getPrompt();

	for (int i = 0; i < 35; i++)
	{
		io.out << prompt << "\n";
	}
}