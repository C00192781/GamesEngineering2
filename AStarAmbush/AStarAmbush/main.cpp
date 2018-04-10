#pragma once
#define SDL_MAIN_HANDLED
#ifdef __APPLE__
#include "SDL2/SDL.h"
#elif defined(_WIN64) || defined(_WIN32)
#include "SDL.h"
#endif


#include "Game.h"
#include <iostream>

int main()
{
	Game* game = new Game();

	game->Initialize();
	game->Load();

	while (game->IsRunning())
	{
		game->Update();
		game->Render();
	}

	SDL_Quit();


	return 0;
}