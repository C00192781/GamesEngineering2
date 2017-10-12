#pragma once
#include "State.h"
#include "Climbing.h"
#include "Jumping.h"

class Idle : public State
{
public:
	Idle();
	~Idle();

	void jumping(Animation* a);
	void climbing(Animation* a);

};