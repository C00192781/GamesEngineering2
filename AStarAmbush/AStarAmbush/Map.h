#pragma once

#include "SDL.h"
#include "Obstacle.h"
#include "NodeObject.h"
#include "Graph.h"
#include "GraphNode.h"
#include "GraphArc.h"
#include "Enemy.h"
#include "Player.h"
#include "EventListener.h"
#include <iostream>
#include <vector>
#include <string>

#include "Agent.h"

using namespace std;


typedef GraphArc<std::string, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;
typedef Agent<pair<std::string, int>, int> theAgent;

class Map
{
public:
	Map(EventListener *eventListener);
	~Map();

	void Draw(SDL_Renderer * renderer);

	std::vector<Obstacle*> map;
	// visual representation of nodes
	std::vector<NodeObject*> nodeObjects;
	std::vector<Enemy*> enemies;

	Player *player;


	Graph< pair<string, int>, int > *graph;
	std::vector<theAgent *> agents;
	Node *pCurrent;


	int numOfAgents;
	int start;
	int goal;

	bool graphInitialized;

	EventListener *m_eventListener;

	void InitializeMap();
	void SpawnOuterWalls();
	void SpawnObstacles();
	void SetNodeRepresentation(int rowWidth, int columnHeight);
	void SetNodes(int rowWidth, int columnHeight);
	void SetArcs(int rowWidth, int columnHeight);
	void SpawnEnemies(int num, SDL_Point start, int width, int height, SDL_Colour colour);
	void SetWaypoints(std::vector<SDL_Point> waypoints);
	void RunAStarAmbush(int i);

	void RemoveNodesInObstacles();

	bool isGraphInitialized() {
		return graphInitialized;
	}

	void InitializeAgents(int num);

	//void SetEnemyPaths(std::vector<Node*> starPath);


	void Update();

private:

	std::vector<SDL_Point> allWaypoints;
};