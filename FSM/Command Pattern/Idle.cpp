#include "Idle.h"
#include "Animation.h"


Idle::Idle()
{

}

Idle::~Idle()
{

}

void Idle::jumping(Animation * a)
{
	std::cout << "Running" << std::endl;
	a->setCurrent(new Jumping());
	delete this;
}

void Idle::climbing(Animation * a)
{
	std::cout << "Climbing" << std::endl;
	a->setCurrent(new Climbing());
	delete this;
}
