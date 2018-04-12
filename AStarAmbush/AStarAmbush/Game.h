
#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <fstream>
#include <string>
#include <utility>  
#include <map> 

#include "Graph.h"
//#include "SFML\Graphics.hpp"

//#include "Agent.h"
#include "EventListener.h"
#include "InputHandler.h"
#include "Map.h"
#include "Obstacle.h"

#include "SDL_thread.h"


#define fps 60
#define window_width 1000
#define window_height 1000

//typedef GraphArc<std::string, int> Arc;
//typedef GraphNode<pair<std::string, int>, int> Node;
//typedef Agent<pair<std::string, int>, int> theAgent;

// Pathfinding thread function
int AStarAmbush(void* data);


class Game {
private:
	void FramerateHandler();
	Uint32 currentTime;
public:
	bool isRunning;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event *e;

	EventListener *listener;
	InputHandler *input;

	

	/*Graph< pair<string, int>, int > *graph;
	std::vector<theAgent *> agents;
	Node *pCurrent;*/

	/*int numOfAgents;
	int start;
	int goal;*/

	//set up a path
	std::vector<Node* > path;

	void Initialize();
	//void GraphSetUp();
	/*void InitializeAgents(int num);*/
	void RunAStarAmbush(int i);
	void Update();
	void Render();

	void WaitForThreads();

	bool IsRunning()
	{
		return isRunning;
	};


	int timer = 0;

};
