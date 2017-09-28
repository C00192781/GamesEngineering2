#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Game {
private:
	bool isRunning;
	SDL_Window* window = nullptr;


public:
	void Initialize();
	void HandleEvents();

	void Update() {};
	void Render() {};
	void CleanUp() {};

	bool IsRunning() 
	{ return isRunning; };
};