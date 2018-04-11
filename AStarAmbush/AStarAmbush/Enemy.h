#pragma once

#ifndef ENEMY_H
#define ENEMY_H


#include "SDL.h"
#define window_width 1080
#define window_height 720

#define StandardWidthAndHeight 50

class Enemy
{
public:
	Enemy(int x, int y, int w, int h, SDL_Colour col, int tag);
	~Enemy();

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

	int agentTag;


};
#endif
