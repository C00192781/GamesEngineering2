#pragma once
#include "Command.h"
#include <iostream>
#include <list>
#include <iterator>

class MacroCommand : public Command {
public:
	/*MacroCommand();
	virtual ~MacroCommand();
	virtual void add(Command*);
	virtual void remove(Command*);
	virtual void execute();*/
private:
	std::list<Command*>* commands;
};