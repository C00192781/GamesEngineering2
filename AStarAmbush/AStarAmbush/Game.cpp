#include "Game.h"


using namespace std;
using std::pair;


//Data access semaphore
SDL_sem* pathLock = NULL;

//The "data buffer"
int pathData = -1;

Map *myMap;

bool initialized = false;



// Critical Section
// Used for running A*mbush
int AStarAmbush(void * data)
{
	//Pre thread random seeding
	srand(SDL_GetTicks());
	if (initialized == false)
	{
		SDL_Delay(1000);
		initialized = true;
	}
	// Starting our pathfinding thread.
	// seeding of random value is done for every thread
	while (true)
	{
		//Wait 
		SDL_Delay(10);

		//Lock
		SDL_SemWait(pathLock);

		pathData++;
		if (pathData > myMap->enemies.size())
		{
			pathData = 0;
		}

		myMap->RunAStarAmbush(pathData);

		// Unlock
		SDL_SemPost(pathLock);

		//Wait 
		SDL_Delay(10);
	}
	return 0;
}

void Game::Initialize()
{
	isRunning = true; // used for while loop in main
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("A*mbush Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	e = new SDL_Event();

	listener = new EventListener();
	input = new InputHandler(listener, e);

	//Initialize semaphore
	pathLock = SDL_CreateSemaphore(1);

	//Run the threads
	srand(SDL_GetTicks());
	SDL_Delay(3000);
	SDL_Thread* threadA = SDL_CreateThread(AStarAmbush, "Thread A", (void*)"Thread A");
	SDL_Delay(16 + rand() % 32);
	SDL_Thread* threadB = SDL_CreateThread(AStarAmbush, "Thread B", (void*)"Thread B");
	SDL_Delay(16 + rand() % 32);
	SDL_Thread* threadC = SDL_CreateThread(AStarAmbush, "Thread C", (void*)"Thread C");
	
	/*graph = new Graph< pair<string, int>, int >(864);*/

	myMap = new Map(listener);
	myMap->InitializeMap();
	myMap->SetNodeRepresentation(100, 100);
	myMap->SetNodes(100, 100);
	myMap->SetArcs(100, 100);
	
	SDL_Colour enemyColour = SDL_Colour{ 102, 255, 255, 255 };
	myMap->SpawnEnemies(49, SDL_Point{ 100, 100 }, 20, 20, enemyColour);

}


void Game::RunAStarAmbush(int i)
{
	myMap->RunAStarAmbush(i);
}

void Game::Update()
{
	FramerateHandler();
	input->HandleInput();
	myMap->Update();
	SDL_RenderPresent(renderer);
}

void Game::FramerateHandler()
{
	currentTime = SDL_GetTicks();
	if ((1000 / fps) > SDL_GetTicks() - currentTime)
	{
		SDL_Delay(1000 / fps - (SDL_GetTicks() - currentTime));
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// Draws everything on Map
	myMap->Draw(renderer);
}

void Game::WaitForThreads()
{
	/*SDL_WaitThread(threadA, NULL);
	SDL_WaitThread(threadB, NULL);
	SDL_WaitThread(threadC, NULL);*/
}

