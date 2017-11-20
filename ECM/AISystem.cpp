#include "AISystem.h"

AISystem::AISystem()
{
}

AISystem::~AISystem()
{
}

void AISystem::addEntity(Entity e)
{

}

void AISystem::update()
{
	std::cout << "AI System Update" << std::endl;
	for (std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		//	std::cout << *it-> << std::endl;
	}
}
