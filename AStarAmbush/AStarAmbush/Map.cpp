#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::Draw()
{
	for (int i = 0; i < map.size(); i++)
	{
		map.at(i).Draw();
	}
}

void Map::InitializeMap()
{

}

void Map::SetUpOuterWalls()
{
}

void Map::SetUpObstacles()
{
}


