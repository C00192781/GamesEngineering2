#include "InputHandler.h"

// Client - creates concrete command object and specifies the receiver
InputHandler::InputHandler()
{
	buttonX = SDLK_k;
	buttonY = SDLK_3;
	buttonA = SDLK_a;
	buttonB = SDLK_b;
}

InputHandler::InputHandler(Receiver* receiver)
{
	buttonA = SDLK_a;
	buttonB = SDLK_b;
	// Input Handler gives the receiver pointer to the command
	buttonA_ = new JumpCommand(receiver);
	buttonB_ = new FireCommand(receiver);
}

void InputHandler::handleInput(SDL_Event* event, bool* isRunning)
{
	if (event->key.keysym.sym == buttonA)
	{
		// implements execute() by invoking the corresponding operations on Receiver
		buttonA_->execute();
	}
	else if (event->key.keysym.sym == buttonB)
	{
		buttonB_->execute();
	}
}
