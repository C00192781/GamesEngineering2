#include "ControlSystem.h"

ControlSystem::ControlSystem()
{
}

ControlSystem::~ControlSystem()
{
}

void ControlSystem::addEntity(Entity* e)
{
	entities.push_back(e);
}

void ControlSystem::update()
{
	std::cout << "Control System Update" << std::endl;
	//for (std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); it++)
	//{
	//	//	std::cout << *it-> << std::endl;
	//}
}