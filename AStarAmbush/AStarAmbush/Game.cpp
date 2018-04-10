#include "Game.h"


using namespace std;
using std::pair;

#define screenWidth 1080
#define screenHeight 720

void Game::Initialize()
{
	isRunning = true; // used for while loop in main
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	e = new SDL_Event();

	listener = new EventListener();
	input = new InputHandler(listener, e);

	//Graph< pair<string, int>, int > graph(16);

	numOfAgents = 3;
	start = 3;
	goal = 9;

	map = new Map();
	
	graph = new Graph< pair<string, int>, int >(16);
	GraphSetUp();
	InitializeAgents(numOfAgents);

	RunAStarAmbush(start, goal, 0);
	pCurrent = graph->nodeArray()[goal];
	graph->displayPath(pCurrent, start);

	RunAStarAmbush(start, goal, 1);
	pCurrent = graph->nodeArray()[goal];
	graph->displayPath(pCurrent, start);

	RunAStarAmbush(start, goal, 2);
	pCurrent = graph->nodeArray()[goal];
	graph->displayPath(pCurrent, start);

}

void Game::GraphSetUp()
{
//	Graph< pair<string, int>, int > graph(16);
	std::string nodeLabel;
	int i = 0;
	ifstream myfile;
	myfile.open("nodes.txt");
	while (myfile >> nodeLabel) 
	{
		// giving each node a string and an integer we'll change later

		graph->addNode(pair<string, int>(nodeLabel, 0), i);
		i++;
	}
	myfile.close();

	myfile.open("arcs.txt");
	int from, to, weight;
	while (myfile >> from >> to >> weight) 
	{
		graph->addArc(from, to, weight);
	}
	myfile.close();
}

void Game::InitializeAgents(int num)
{
	for (int i = 0; i < num; i++)
	{
		theAgent *agent = new theAgent();
		agent->m_currentAgent = i;
		agents.push_back(agent);
	}

	std::cout << "Number of agents initialized: " << agents.size() << std::endl;
}

void Game::RunAStarAmbush(int start, int goal, int agent)
{
	graph->aStarAmbush(graph->nodeArray()[start], graph->nodeArray()[goal], agents, agents.at(agent));
}

void Game::Load()
{

}

void Game::Update()
{
	FramerateHandler();
	input->HandleInput();
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

}


