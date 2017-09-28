#pragma once
#include "Command.h"


class JumpCommand : public Command
{
public:
	JumpCommand(Receiver* receiver) { pReceiver = receiver; };
	// defines a binding between a receiver object and an action
	virtual void execute() { pReceiver->Action("Jump"); } 
	
};
