#pragma once
#include "Receiver.h"
// Command Interface
class Command
{
public:
	virtual ~Command() {}
	virtual void execute() = 0;
protected:
	Receiver* pReceiver;
	Command() {}
	Command(Receiver* receiver) { pReceiver = receiver; };
};