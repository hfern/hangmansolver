#pragma once
#include <string>
#include "WordSet.h"
#include <iostream>
#include <sstream>


struct IOHelper
{
	std::istream& in;
	std::ostream& out;

	IOHelper(std::istream& instream, std::ostream& outstream) : in(instream), out(outstream) {};
};

class CommandRunner;

class Command
{
protected:
	
	IOHelper& io;
	CommandRunner* runner;

public:
	// Helptext returns a pair of two strings
	// The first containing the argument helper string
	// and the second containing the text for what the command
	// actually does.
	virtual std::pair<std::string, std::string> helptext() const = 0;

	// Call invokes the command with the using wordset and the 
	// rest of the invokation line (minus the command's name).
	virtual void call(WordSet& wordset, std::string args) = 0;

	// The the command runner for the given command instance.
	void set_runner(CommandRunner* cr);

	explicit Command(IOHelper& ioh);
	virtual ~Command();

protected:
	std::string trim(std::string, const std::string& delimiters = " \f\n\r\t\v");
};

