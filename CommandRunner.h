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

	std::string prompt = "~ ";

public:

	CommandRunner(std::istream& in, std::ostream& out, WordSet& wordset);
	~CommandRunner();

	void Run(); // Interactively run 
	const CommandMap* Commands() const; // Get the registered commands.
	std::string getPrompt() const; // get the prompt of the console sess.


	// Template function to allow easy registration of polymorphic commands 
	// Use by runner.RegisterCommand<MyCustomCommandClass>("calledWithThisName");
	template <typename CommandClassName>
	void RegisterCommand(std::string commandName)
	{
		Command* comm = new CommandClassName(ioh);
		comm->set_runner(this);

		commands[commandName] = comm;
	}
};

