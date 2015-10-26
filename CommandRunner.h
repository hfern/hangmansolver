#pragma once
#include "Command.h"
#include <map>
#include <string>

class CommandRunner
{
public:
	using CommandMap = std::map<std::string, Command*>;
private:
	IOHelper ioh;
	CommandMap commands;
	WordSet& wordset;

public:

	CommandRunner(std::istream& in, std::ostream& out, WordSet& wordset);
	~CommandRunner();

	void Run(); // Interactively run 

	const CommandMap* Commands() const;

	// Template function to allow easy registration of polymorphic commands 
	template <typename CommandType>
	void RegisterCommand(std::string name)
	{
		Command* comm = new CommandType(ioh);
		comm->set_runner(this);

		commands[name] = comm;
	}
};

