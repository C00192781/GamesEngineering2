#include "Enemy.h"

Enemy::Enemy(int x, int y, int w, int h, SDL_Colour col, int tag)
{
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	colour = col;

	rect = { xPos, yPos, width, height };
	xSpeed = 0;
	ySpeed = 0;
}

Enemy::~Enemy()
{

}

void Enemy::Draw(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Enemy::Move(int x, int y)
{
		
}
