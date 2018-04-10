#pragma once

#include "Obstacle.h"
#include "NodeObject.h"
#include "Graph.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Map
{
public:
	Map();
	~Map();

	void Draw(SDL_Renderer * renderer);

	std::vector<Obstacle*> map;
	// visual representation of nodes
	std::vector<NodeObject*> nodeObjects;
	void InitializeMap();
	void SetUpOuterWalls();
	void SetUpObstacles();
	void SetNodeRepresentation(int rowWidth, int columnHeight);
	void SetNodes(int rowWidth, int columnHeight, Graph<pair<string, int>, int> *graph);

private:
};