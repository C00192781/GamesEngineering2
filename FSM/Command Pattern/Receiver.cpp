#include "Receiver.h"
#include "Animation.h"




void Receiver::Action(std::string action)
{
	if (action == "Jump")
	{
		Jump();
	}
	if (action == "Fire")
	{
		Fire();
	}
}

void Receiver::Jump()
{
	//std::cout << "Jump" << std::endl;

	

}

void Receiver::Fire()
{
	//std::cout << "Fire" << std::endl;
}
