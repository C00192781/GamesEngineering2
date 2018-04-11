#include "Player.h"

Player::Player(int x, int y, int w, int h, SDL_Colour col)
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

Player::~Player()
{
}

void Player::Draw(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Player::Move(int x, int y)
{
	rect.x += x;
	rect.y += y;
}
