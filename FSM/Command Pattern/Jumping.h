#pragma once
#include "State.h"
#include "Idle.h"

class Jumping : public State
{
public:
	Jumping();
	~Jumping();
	void idle(Animation* a);
	void Animate();
};