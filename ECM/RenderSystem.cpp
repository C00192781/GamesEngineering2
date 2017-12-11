#include "RenderSystem.h"

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::addEntity(Entity* e)
{
	entities.push_back(e);
}

void RenderSystem::update()
{
	std::cout << "Render System Update" << std::endl;
	//for (std::vector<Entity>::iterator it = entities.begin(); it != entities.end(); it++)
	//{
	//	//	std::cout << *it-> << std::endl;
	//}
}