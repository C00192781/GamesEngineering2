#pragma once
#include "Command.h"


class FireCommand : public Command
{
public:
	FireCommand(Receiver* receiver) { pReceiver = receiver; };
	// defines a binding between a receiver object and an action
	virtual void execute() { pReceiver->Action("Fire"); }

};