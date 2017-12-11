#pragma once

#include "Entity.h"
#include <iostream>

class AISystem
{
	std::vector<Entity*> entities;

public:
	AISystem();
	~AISystem();
	void addEntity(Entity* e);
	void update();
	bool check = false;
	bool getCheck();

	bool start = false;
	bool getStart() 
	{
		return start;
	}
	bool end = false;
	bool getEnd() 
	{
		return end;
	}

	bool start2 = false;
	bool getStart2()
	{
		return start2;
	}
	bool end2 = false;
	bool getEnd2()
	{
		return end2;
	}
};