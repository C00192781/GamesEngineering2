#include "Game.h"
#include "InputHandler.h"
#include <iostream>




void Game::Initialize()
{
	isRunning = true; // used for while loop in main
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = IMG_LoadTexture(renderer, "Assets/spriteSheet.png");
	frame = 0;

}

void Game::HandleEvents()
{
	// pointer to the receiver class
	Receiver * receiver = new Receiver();
	SDL_Event event;
	// pass this receiver pointer into the input handler
	InputHandler input = InputHandler(receiver);

	// IMPORTANT CALCULATION - outputted image based on current frame
	currentRect = &fsm.getRect()[frame / 6];
	fsm.animateCurrent();

	// clear the screen
	SDL_RenderClear(renderer);

	// Basically, the sprite sheet array is retrieved depending on the state
	// the currentRect is calculated 3 lines above
	SDL_RenderCopy(renderer, texture, currentRect, fsm.getRect());
	//SDL_RenderCopy(renderer, texture, fsm.getCurrentRect(), fsm.getRect());

	// flip the backbuffer
	// this means that everything that we prepared behind the screens is actually shown
	SDL_RenderPresent(renderer);

	FrameHandler();
	FramerateHandler();


	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			// input
			if (event.key.keysym.sym == SDLK_a)
			{
				fsm.jumping();
			}
			else if (event.key.keysym.sym == SDLK_b)
			{
				fsm.climbing();
			}
			else if (event.key.keysym.sym == SDLK_c)
			{
				fsm.idle();
			}
		}
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}
		// pass the sdl event into input handler
		input.handleInput(&event, &isRunning);
	}
}

// Handles how the frame value is cycled through
void Game::FrameHandler()
{
	frame++;
	//s.setFrame(frame);
	//std::cout << fsm.getRect() << std::endl;
	if (frame / 6 >= 6)
	{
		frame = 0;
	}
	//frame = fsm.getFrame();
	
	if (frame / 6 >= 6)
	{
		frame = 0;
	}

}


void Game::FramerateHandler()
{
	starting_tick = SDL_GetTicks();
	if ((1000 / fps) > SDL_GetTicks() - starting_tick)
	{
		SDL_Delay(1000 / fps - (SDL_GetTicks() - starting_tick));
	}
}