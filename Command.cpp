#include "Command.h"


void Command::set_runner(CommandRunner* cr)
{
	runner = cr;
}

Command::Command(IOHelper& ioh): io(ioh)
{

}

Command::~Command()
{
}

std::string Command::trim(std::string s, const std::string& delimiters)
{
	std::string right_trimmed = s.erase(s.find_last_not_of(delimiters) + 1);
	return right_trimmed.erase(0, right_trimmed.find_first_not_of(delimiters));
}