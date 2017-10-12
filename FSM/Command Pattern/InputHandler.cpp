#include "InputHandler.h"

// Client (View) - creates concrete command object and specifies the receiver
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
	// Input Handler gives the Receiver pointer to the command
	buttonA_ = new JumpCommand(receiver);
	buttonB_ = new FireCommand(receiver);
}

void InputHandler::handleInput(SDL_Event* event, bool* isRunning)
{
	if (event->key.keysym.sym == buttonA)
	{
		buttonA_->execute();
	}
	else if (event->key.keysym.sym == buttonB)
	{
		buttonB_->execute();
	}
}
