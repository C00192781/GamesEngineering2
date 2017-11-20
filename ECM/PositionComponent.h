#pragma once

// COMPONENT

#include "Component.h"


class PositionComponent : public Component
{
private:
	SDL_Point position;

public:
	PositionComponent() : position{ 100, 100 } {};

	SDL_Point getPosition() { return position; }
	void setPosition(SDL_Point pos) { position = pos; }
};
