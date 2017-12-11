#pragma once

//#include "SDL.h"

class Component
{
public:
	Component() {};
	virtual ~Component() {};
	int componentID = 0;

	void setComponentID(int val) 
	{ 
		componentID = val; 
	}
	int getID()
	{
		return componentID;
	}
};