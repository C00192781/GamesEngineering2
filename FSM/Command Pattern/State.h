#pragma once
//#include "Animation.h"
#include <SDL.h>
#include <iostream>


class State
{
public:
	class Animation* a;
	int WALKING_ANIMATION_FRAMES;
	SDL_Rect sheetRect[10];
	SDL_Rect* currentRect;
	int frame = 0;
	int frameTotal = 0;
	virtual void idle(Animation* a)
	{
		std::cout << "State::Idling" << std::endl;
	}

	virtual void jumping(Animation* a)
	{
		std::cout << "State::Jumping" << std::endl;
	}

	virtual void climbing(Animation* a)
	{
		std::cout << "State::Climbing" << std::endl;
	}

	virtual void Animate() {};

	int setFrame(int s)
	{
		frame = s;
		return frame;
	}

	virtual SDL_Rect* setCurrentRect(SDL_Rect& rect)
	{
		currentRect = &rect;
		return currentRect;
	}
};