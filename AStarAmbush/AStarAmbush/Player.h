#pragma once

#ifndef PLAYER_H
#define PLAYER_H


#include "SDL.h"
#define window_width 1080
#define window_height 720

#define StandardWidthAndHeight 50

class Player
{
public:
	Player(int x, int y, int w, int h, SDL_Colour col);
	~Player();

	void Draw(SDL_Renderer * renderer);
	void Move(int x, int y);


private:
	SDL_Rect rect;
	SDL_Point position;
	SDL_Colour colour;

	int xPos;
	int yPos;
	int width;
	int height;

	int xSpeed;
	int ySpeed;


};
#endif
