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
	virtual std::pair<std::string, std::string> helptext() const = 0;
	virtual void call(WordSet& wordset, std::string args) = 0;

	void set_runner(CommandRunner* cr);

	explicit Command(IOHelper& ioh);
	virtual ~Command();

protected:
	std::string trim(std::string, const std::string& delimiters = " \f\n\r\t\v");
};

