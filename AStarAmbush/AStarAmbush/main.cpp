#pragma once
#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif


#include "Game.h"
#include <iostream>

// Written By: Kevin Boylan
// WSAD - Controls Player
// Implementation of A*ambush (uses agents and calculates degree) included
// Threading for Critical Section - Running A*mbush
// Enemies target player position
// No Collision Detection

int main()
{
	Game* game = new Game();

	game->Initialize();

	while (game->IsRunning())
	{
		game->Update();
		game->Render();
	}

	game->WaitForThreads();
	SDL_Quit();


	return 0;
}