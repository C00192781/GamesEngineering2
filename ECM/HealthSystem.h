#pragma once

#include "Entity.h"
#include <iostream>

class HealthSystem
{
	std::vector<Entity> entities;

public:
	void addEntity(Entity e) {}
	void update()
	{
		std::cout << "HealthSystem Update" << std::endl;
		for (std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); it++)
		{
		//	std::cout << *it-> << std::endl;
		}
	}
};