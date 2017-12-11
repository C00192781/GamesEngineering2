#include <iostream>
#include "Component.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "ControlComponent.h"
#include "Entity.h"
#include "AISystem.h"
#include "ControlSystem.h"
#include "RenderSystem.h"

//#include <SDL.h>
#undef main

bool isRunning;
//SDL_Window* window = nullptr;

void Initialize()
{
	isRunning = true; // used for while loop in main
	//SDL_Init(SDL_INIT_EVERYTHING);
	//window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_SHOWN);
}


int main(void*)
{
	Initialize();

	// PLAYER
	Entity* player = new Entity();

	HealthComponent* playerHealth = new HealthComponent();
	playerHealth->setHealth(100);
	//PositionComponent* playerPos = new PositionComponent();
	//playerPos->setPosition(SDL_Point{ 10, 20 });

	playerHealth->setComponentID(3);
	
	ControlComponent* playerControl = new ControlComponent();
	playerControl->setKeyPressed(true);
	
	player->addComponent(playerHealth);
	//player->addComponent(playerPos);
	player->addComponent(playerControl);


	// ALIEN
	Entity* alien = new Entity();

	HealthComponent* alienHealth = new HealthComponent();
	alienHealth->setHealth(70);
	//PositionComponent alienPos = PositionComponent();
//	alienPos.setPosition(SDL_Point{ 70, 100 });

//	alien->addComponent(alienHealth);
//	alien->addComponent(alienPos);


	// DOG
	Entity* dog = new Entity();

	HealthComponent* dogHealth = new HealthComponent();
	dogHealth->setHealth(15);
	//PositionComponent* dogPos = new PositionComponent();
	//dogPos->setPosition(SDL_Point{ 300, -44 });

	dog->addComponent(dogHealth);
	//dog->addComponent(dogPos);


	// CAT
	Entity* cat = new Entity();

	HealthComponent* catHealth = new HealthComponent();
	catHealth->setHealth(10);
	//PositionComponent* catPos = new PositionComponent();
	//catPos->setPosition(SDL_Point{ 330, -50 });

	cat->addComponent(catHealth);
	//cat->addComponent(catPos);



	// SYSTEMS
	AISystem* aiSystem = new AISystem();
	aiSystem->addEntity(player);
	aiSystem->addEntity(alien);
	aiSystem->addEntity(dog);
	aiSystem->addEntity(cat);

	RenderSystem* renderSystem = new RenderSystem();
	renderSystem->addEntity(player);
	renderSystem->addEntity(alien);
	renderSystem->addEntity(dog);
	renderSystem->addEntity(cat);

	ControlSystem* controlSystem = new ControlSystem();
	controlSystem->addEntity(player);



	while (true)
	{
		/*SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}*/

		// system updates
		aiSystem->update();
		renderSystem->update();
		controlSystem->update();
	}


	system("PAUSE");
	return 0;
}





