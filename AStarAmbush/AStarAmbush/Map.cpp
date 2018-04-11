#include "Map.h"

Map::Map()
{

}

Map::~Map()
{

}

void Map::Draw(SDL_Renderer * renderer)
{
	/*std::cout << nodeObjects.size() << std::endl;*/
	/*for (int i = 0; i < nodeObjects.size(); i++)
	{
		nodeObjects.at(i)->Draw(renderer);
	}
	for (int i = 0; i < map.size(); i++)
	{
		map.at(i)->Draw(renderer);
	}*/
	for (int i = 0; i < map.size(); i++)
	{
		map.at(i)->Draw(renderer);
	}
	for (int i = 0; i < nodeObjects.size(); i++)
	{
		nodeObjects.at(i)->Draw(renderer);
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

void Map::SetNodeRepresentation(int rowWidth, int columnHeight)
{
	for (int i = 0; i < rowWidth; i++)
	{
		for (int y = 0; y < columnHeight; y++)
		{
			SDL_Colour green = SDL_Colour{ 25, 179, 0, 0 };
			NodeObject *nodeObject = new NodeObject(i * 30, y * 30, 5, 5, green);
			nodeObjects.push_back(nodeObject);
		}
	}
}

void Map::SetNodes(int rowWidth, int columnHeight, Graph< pair<string, int>, int > *graph)
{
	int count = 0;
	for (int i = 0; i < rowWidth; i++)
	{
		for (int y = 0; y < columnHeight; y++)
		{
			SDL_Point position = SDL_Point{ i * 30, y * 30 };
			graph->addNode(pair<string, int>(std::to_string(count), 0), count, position);
			count++;
		}
	}
}

void Map::SetArcs(int rowWidth, int columnHeight, Graph<pair<string, int>, int>* graph)
{
	int standardWeight = 30;

	//std::cout << graph->getSize();
	int size = graph->getSize();

	int x = 0;
	int y = 0;

	for (int i = 0; i < size; i++)
	{
		SDL_Point waypoint = SDL_Point{ graph->nodeArray()[i]->getWaypoint().x, graph->nodeArray()[i]->getWaypoint().y };
		x = waypoint.x / 30 + 1; // column 
		y = waypoint.y / 30 + 1; // row

		//std::cout << waypoint.x << " " << waypoint.y << std::endl;

		int check = x * columnHeight - 1;
		//int check2 = (x - 1) * columnHeight - 1;
		//int check3 = (x + 1) * columnHeight - 1;

		// up
		if (i - 1 > check - columnHeight)
		{
			graph->addArc(i, i - 1, standardWeight);
		}
		// down 
		if (i + 1 < check + 1)
		{
			graph->addArc(i, i + 1, standardWeight);
		}
		// left
		if ((i - 24 > check - (columnHeight* 2)) && ((check - columnHeight) >=0))
		{
			graph->addArc(i, i - columnHeight, standardWeight);
		}
		// right
		if ((i + 24 < check + columnHeight + 1) && ((check + columnHeight) <= (size + 1))  )
		{
			graph->addArc(i, i + columnHeight, standardWeight);
		}

		//std::cout << (check - columnHeight) << std::endl;

		//std::cout << "x: " << x << std::endl;
		//std::cout << "y: " << y << std::endl;
		//std::cout << "Index: " << graph->nodeArray()[i]->data().first << std::endl;

		//std::cout << "Size: " << graph->nodeArray()[i]->arcList().size() << std::endl;
	}
}


