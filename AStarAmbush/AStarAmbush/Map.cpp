#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::Draw(SDL_Renderer * renderer)
{
	for (int i = 0; i < map.size(); i++)
	{
		map.at(i)->Draw(renderer);
	}
}

void Map::InitializeMap()
{
	SetUpOuterWalls();
	SetUpObstacles();
}

void Map::SetUpOuterWalls()
{
	SDL_Colour red = SDL_Colour{ 220, 0, 0, 0 };
	Obstacle *leftWall = new Obstacle(0, 0, StandardWidthAndHeight, window_height, red);
	Obstacle *rightWall = new Obstacle(window_width - StandardWidthAndHeight, 0, StandardWidthAndHeight, window_height, red);
	Obstacle *topWall = new Obstacle(0, 0, window_width, StandardWidthAndHeight, red);
	Obstacle *downWall = new Obstacle(0, window_height - StandardWidthAndHeight, window_width, StandardWidthAndHeight, red);
	
	map.push_back(leftWall);
	map.push_back(rightWall);
	map.push_back(topWall);
	map.push_back(downWall);
}

void Map::SetUpObstacles()
{
	SDL_Colour red = SDL_Colour{ 220, 0, 0, 0 };
	Obstacle *obstacle1 = new Obstacle(200, 0, StandardWidthAndHeight, window_height/1.5, red);
	Obstacle *obstacle2 = new Obstacle(500, 150, StandardWidthAndHeight, window_height/1.5, red);
	Obstacle *obstacle3 = new Obstacle(800, 100, StandardWidthAndHeight, window_height/1.5, red);
	map.push_back(obstacle1);
	map.push_back(obstacle2);
	map.push_back(obstacle3);
}


