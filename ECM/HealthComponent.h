#pragma once

// COMPONENT

#include "Component.h"

class HealthComponent : public Component
{
private:
	int m_health;

public: 
	HealthComponent() : m_health(100), componentID(2) {
		componentID = 2;
	};

	int getHealth() { return m_health; }
	void setHealth(int myHealth) { m_health = myHealth; }

	int componentID = 2;
};
