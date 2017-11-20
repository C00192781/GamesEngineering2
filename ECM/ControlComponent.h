#pragma once

// COMPONENT

#include "Component.h"

class ControlComponent : public Component
{
public:
	ControlComponent() : m_health(100) {};

	/*int getHealth() { return m_health; }
	void setHealth(int myHealth) { m_health = myHealth; }*/

private:
	int m_health;
};