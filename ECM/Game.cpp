#include <iostream>
#include "Component.h"
#include "HealthComponent.h"
#include "Entity.h"
#include "HealthSystem.h"



int main()
{
	Entity player = Entity();
	HealthComponent hc = HealthComponent();
	player.addComponent(hc);
	
	HealthSystem hs = HealthSystem();
	hs.addEntity(player);

	while (true)
	{
		hs.update();
	}


	system("PAUSE");
	return 0;
}