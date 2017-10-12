#pragma once
#include "Command.h"
#include "JumpCommand.h"
#include "FireCommand.h"
#include "Receiver.h"
#include <SDL.h>
#include <iostream>


// Client - creates a concrete command object and specifies the receiver
class InputHandler
{
public:
	void handleInput(SDL_Event* event, bool* isRunning);
	
	InputHandler();
	InputHandler(Receiver* receiver);


private:
	Command* buttonX_;
	Command* buttonY_; 
	Command* buttonA_; // Jump
	Command* buttonB_; // Fire

	SDL_Keycode buttonX; 
	SDL_Keycode buttonY;
	SDL_Keycode buttonA;
	SDL_Keycode buttonB;

};