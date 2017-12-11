#include "AISystem.h"

AISystem::AISystem()
{
}

AISystem::~AISystem()
{
}

void AISystem::addEntity(Entity* e)
{
	entities.push_back(e);
}


bool AISystem::getCheck()
{
	return check;
}

void AISystem::update()
{
	std::cout << "AI System Update" << std::endl;
	for (std::vector<Entity*>::iterator iter = entities.begin(); iter != entities.end(); iter++)
	{
		std::cout << "Cycle through AI Entities" << std::endl;
		
		std::vector<Component*> tempVector = (*iter)->getComponents();
		start = true;
		end = false;
		
		for (std::vector<Component*>::iterator tempIter = tempVector.begin(); tempIter != tempVector.end(); tempIter++)
		{
			start2 = true;
			end2 = false; 
			if ((*tempIter)->getID() == 4)
			{
				std::cout << "Component doesn't Update" << std::endl;
				check = false;
			}
			else if ((*tempIter)->getID() == 5)
			{
				std::cout << "Component Updates" << std::endl;
				check = true;
			}
		}
		start2 = false;
		end2 = true;
	}
	start = false;
	end = true;
}






