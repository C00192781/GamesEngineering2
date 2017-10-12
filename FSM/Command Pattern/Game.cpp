#include "Game.h"
#include "InputHandler.h"
#include <iostream>




void Game::Initialize()
{
	isRunning = true; // used for while loop in main
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
	//SDL_Surface* screen;
	//image = SDL_LoadBMP("");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	texture = IMG_LoadTexture(renderer, "Assets/spriteSheet.png");
	frame = 0;

	//screen = SDL_GetWindowSurface(window);
	//white = SDL_MapRGB(screen->format, 255, 255, 255);
	//SDL_FillRect(screen, NULL, white);


	/*sheetRect[0].x = 0;
	sheetRect[0].y = 0;
	sheetRect[0].w = 163;
	sheetRect[0].h = 290;

	sheetRect[1].x = 163;
	sheetRect[1].y = 0;
	sheetRect[1].w = 163;
	sheetRect[1].h = 290;

	sheetRect[2].x = 326;
	sheetRect[2].y = 0;
	sheetRect[2].w = 163;
	sheetRect[2].h = 290;

	sheetRect[3].x = 489;
	sheetRect[3].y = 0;
	sheetRect[3].w = 163;
	sheetRect[3].h = 290;

	sheetRect[4].x = 652;
	sheetRect[4].y = 0;
	sheetRect[4].w = 163;
	sheetRect[4].h = 290;

	sheetRect[5].x = 815;
	sheetRect[5].y = 0;
	sheetRect[5].w = 163;
	sheetRect[5].h = 290;

	sheetRect[6].x = 978;
	sheetRect[6].y = 0;
	sheetRect[6].w = 163;
	sheetRect[6].h = 290;

	sheetRect[7].x = 1141;
	sheetRect[7].y = 0;
	sheetRect[7].w = 163;
	sheetRect[7].h = 290;

	sheetRect[8].x = 1304;
	sheetRect[8].y = 0;
	sheetRect[8].w = 163;
	sheetRect[8].h = 290;

	sheetRect[9].x = 1467;
	sheetRect[9].y = 0;
	sheetRect[9].w = 163;
	sheetRect[9].h = 290;*/

}

void Game::HandleEvents()
{
	// pointer to the receiver class
	Receiver * receiver = new Receiver();
	SDL_Event event;
	// pass this receiver pointer into the input handler
	InputHandler input = InputHandler(receiver);

	//currentRect = &sheetRect[frame / 10];*/
	currentRect = &fsm.getRect()[frame / 6];
	fsm.animateCurrent();
	//std::cout << frame << std::endl;
	//SDL_RenderCopy(renderer, texture, sheetRect, currentRect);
	// clear the screen
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, texture, currentRect, fsm.getRect());
	//SDL_RenderCopy(renderer, texture, fsm.getCurrentRect(), fsm.getRect());

	// flip the backbuffer
	// this means that everything that we prepared behind the screens is actually shown
	SDL_RenderPresent(renderer);

	FrameHandler();
	FramerateHandler();

	//SDL_UpdateWindowSurface(window);


	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
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