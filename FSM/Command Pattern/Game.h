#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Animation.h"
#include "State.h"

#define fps 60
#define window_width 1000
#define window_height 800


class Game {
private:
	bool isRunning;
	SDL_Window* window = nullptr;

	//const int WALKING_ANIMATION_FRAMES = 10;
	//SDL_Rect sheetRect[10];
	// used for rendering the current frame
	SDL_Texture* texture = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Rect* currentRect;

	SDL_Surface *screen;
	Uint32 white;
	Uint32 starting_tick;
	
	int frame = 0;

	void FramerateHandler();

	Animation fsm;
	State s;

public:
	void Initialize();
	void HandleEvents();

	void FrameHandler();

	void Update() {};
	void Render() {};
	void CleanUp() {};

	bool IsRunning() 
	{ return isRunning; };
};