#pragma once
#include "Command.h"

namespace Commands
{

	// Set the length of the target word
	class SetLength: public Command
	{
	public:
		SetLength(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};

	// set a known character
	class SetCharacter: public Command
	{
	public:
		SetCharacter(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};

	// mark a letter as being unused
	class SetNo: public Command
	{
	public:
		SetNo(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};

	// list the remaining potential words
	class Words: public Command
	{
	public:
		Words(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};

	// list the usable commands :)
	class Help: public Command
	{
	public:
		Help(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};

	// list the count of the remaining potential words
	class Count : public Command
	{
	public:
		Count(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};

	// reset the game
	class Reset : public Command
	{
	public:
		Reset(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};

	// perform a lexical analysis of remaining words
	// to find which letter most contain
	class Analyze : public Command
	{
	public:
		Analyze(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};

	// clear the console
	class Clear : public Command
	{
	public:
		Clear(IOHelper& ioh) : Command(ioh) {};
		std::pair<std::string, std::string> helptext() const override;
		void call(WordSet& wordset, std::string args) override;
	};
}