#pragma once

#ifndef NODEOBJECT_H
#define NODEOBJECT_H


#include "SDL.h"
#define window_width 1080
#define window_height 720

class NodeObject
{
public:
	NodeObject(int x, int y, int w, int h, SDL_Colour col);
	~NodeObject();

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