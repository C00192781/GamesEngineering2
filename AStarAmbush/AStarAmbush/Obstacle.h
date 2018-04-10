#pragma once

#ifndef OBSTACLE_H
#define OBSTACLE_H


#include "SDL.h"

class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	void Draw();


private:
	SDL_Rect rect;
	SDL_Point position;
	SDL_Point colour;

	int xPos;
	int yPos;
	int width;
	int height;


};
#endif