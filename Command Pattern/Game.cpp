#include "Game.h"
#include "InputHandler.h"
#include <iostream>



void Game::Initialize()
{
	isRunning = true; // used for while loop in main
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
}

void Game::HandleEvents()
{
	// pointer to the receiver class
	Receiver * receiver = new Receiver();
	SDL_Event event;
	// pass this receiver pointer into the input handler
	InputHandler input = InputHandler(receiver);

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}

		// pass the sdl event into input handler
		input.handleInput(&event, &isRunning);
		
	}
}