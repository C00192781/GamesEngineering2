#pragma once

#include "Obstacle.h"
#include <iostream>
#include <vector>

using namespace std;

class Map
{
public:
	Map();
	~Map();

	void Draw(SDL_Renderer * renderer);

	std::vector<Obstacle*> map;
	void InitializeMap();
	void SetUpOuterWalls();
	void SetUpObstacles();

private:
};