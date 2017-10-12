#pragma once
#include "SDL.h"
class Animation
{
public:
	class State* current;
	Animation();
	void setCurrent(State* s)
	{
		current = s;
	}
	void idle();
	void jumping();
	void climbing();
	void animateCurrent();
	SDL_Rect* getRect();
	int getFrame();
	int getFrameTotal();
	
	
};