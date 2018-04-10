#include "Obstacle.h"

Obstacle::Obstacle(int x, int y, int w, int h, SDL_Colour col)
{
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	colour = col;

	rect = { xPos, yPos, width, height };
}

Obstacle::~Obstacle()
{

}

void Obstacle::Draw(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(renderer, &rect);
}
