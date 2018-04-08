#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "SDL_image.h"

#include <iostream>
#include <fstream>
#include <string>
#include <utility>  
#include <map> 

#include "Graph.h"
//#include "SFML\Graphics.hpp"

#include "Agent.h"
#include "EventListener.h"
#include "InputHandler.h"


using namespace std;
using std::pair;

#define screenWidth 1080
#define screenHeight 720



typedef GraphArc<std::string, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;
typedef Agent<std::pair<std::string, int>, int> theAgent;

int main(int argc, char *argv[]) {

	//sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Project");
	SDL_Window* gameWindow = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 816, 624, SDL_WINDOW_SHOWN);
	SDL_Renderer* gameRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Event *e = new SDL_Event();

	EventListener *listener = new EventListener();

	InputHandler *input = new InputHandler(listener, e);
	
	Graph< pair<string, int>, int > graph(16);
	std::string nodeLabel;

	int i = 0;
	ifstream myfile;
	myfile.open ("nodes.txt");

	while ( myfile >> nodeLabel ) {
	// giving each node a string and an integer we'll change later

		graph.addNode(pair<string,int>(nodeLabel, 0), i);
		i++;
	}
	myfile.close();

	myfile.open("arcs.txt");

	int from, to, weight;
	while ( myfile >> from >> to >> weight ) {
		graph.addArc(from, to, weight);
	}
    myfile.close();

	std::vector<theAgent *> agents;
	theAgent agent;
	agent.m_currentAgent = 0;
	agents.push_back(&agent);
	theAgent agent2;
	agent2.m_currentAgent = 1;
	agents.push_back(&agent2);
	theAgent agent3;
	agent3.m_currentAgent = 2;
	agents.push_back(&agent3);


	//set up a path
	std::vector<Node* > path;

	int start = 0;
	int goal = 24;

	while (true)
	{
		cout << "Provide starting point" << endl;
		cin >> start;
		cout << "Provide goal" << endl;
		cin >> goal;

		graph.aStarAmbush(graph.nodeArray()[start], graph.nodeArray()[goal], agents, agents.at(0));
		//graph.aStar(graph.nodeArray()[start], graph.nodeArray()[goal], path);
		// set up a pointer to the Goal Node
		Node *pCurrent = graph.nodeArray()[goal];
		// used to output path + path values
		while (pCurrent != graph.nodeArray()[start])
		{
			std::cout << "Node: " << pCurrent->data().first << std::endl;
			std::cout << "Distance: " << pCurrent->data().second << std::endl;

			std::cout << "Estimate: " << pCurrent->getEstimate() << std::endl;
			pCurrent = pCurrent->getPrevious();
		}

		std::cout << std::endl;

		//for (int index = 0; index < agent.starPath.size(); index++)
		//{
		//	if (agent.starPath.at(index) == graph.nodeArray()[goal])
		//	{
		//		std::cout << "start" << std::endl;
		//	}
		//	std::cout << agent.starPath.at(index)->data().first << " " << agent.starPath.at(index)->data().second << std::endl;
		//}

		for (int index = agent.starPath.size() - 1; index > -1; index--)
		{
			std::cout << agent.starPath.at(index)->data().first << " " << agent.starPath.at(index)->data().second << std::endl;
			if (agent.starPath.at(index) == graph.nodeArray()[goal])
			{
				std::cout << "complete" << std::endl;
			}
		}

		graph.aStarAmbush(graph.nodeArray()[start], graph.nodeArray()[goal], agents, agents.at(1));
		//graph.aStar(graph.nodeArray()[start], graph.nodeArray()[goal], path);
		// set up a pointer to the Goal Node
		pCurrent = graph.nodeArray()[goal];
		// used to output path + path values
		while (pCurrent != graph.nodeArray()[start])
		{
			std::cout << "Node: " << pCurrent->data().first << std::endl;
			std::cout << "Distance: " << pCurrent->data().second << std::endl;

			std::cout << "Estimate: " << pCurrent->getEstimate() << std::endl;
			pCurrent = pCurrent->getPrevious();
		}

		std::cout << std::endl;

		for (int index = agent2.starPath.size() - 1; index > -1; index--)
		{
			std::cout << agent2.starPath.at(index)->data().first << " " << agent2.starPath.at(index)->data().second << std::endl;
			if (agent2.starPath.at(index) == graph.nodeArray()[goal])
			{
				std::cout << "complete" << std::endl;
			}
		}
		//input->HandleInput();
	}
	SDL_RenderPresent(gameRenderer);

	SDL_DestroyRenderer(gameRenderer);
	SDL_DestroyWindow(gameWindow);

	IMG_Quit();
	SDL_Quit();


	system("PAUSE");
}


