#pragma once

#ifndef OBSTACLE_H
#define OBSTACLE_H


#include "SDL.h"
#define window_width 1080
#define window_height 720

#define StandardWidthAndHeight 50

class Obstacle
{
public:
	Obstacle(int x, int y, int w, int h, SDL_Colour col);
	~Obstacle();

	void Draw(SDL_Renderer * renderer);


private:
	SDL_Rect rect;
	SDL_Point position;
	SDL_Colour colour;

	int xPos;
	int yPos;
	int width;
	int height;


};
#endif