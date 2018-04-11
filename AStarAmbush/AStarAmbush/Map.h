#pragma once

#include "Obstacle.h"
#include "NodeObject.h"
#include "Graph.h"
#include "Enemy.h"
#include "Player.h"
#include "EventListener.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

	EventListener *m_eventListener;

	void InitializeMap();
	void SpawnOuterWalls();
	void SpawnObstacles();
	void SetNodeRepresentation(int rowWidth, int columnHeight);
	void SetNodes(int rowWidth, int columnHeight, Graph<pair<string, int>, int> *graph);
	void SetArcs(int rowWidth, int columnHeight, Graph<pair<string, int>, int> *graph);
	void SpawnEnemies(int num, SDL_Point start, int width, int height, SDL_Colour colour);


	void Update();

private:
};