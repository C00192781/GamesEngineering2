#pragma once

#include "Entity.h"
#include <iostream>

class RenderSystem
{
	std::vector<Entity> entities;

public:
	RenderSystem();
	~RenderSystem();
	void addEntity(Entity e);
	void update();
};
