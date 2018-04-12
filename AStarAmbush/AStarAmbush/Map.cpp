#include "Map.h"

Map::Map(EventListener *eventListener)
{
	m_eventListener = eventListener;
	graph = new Graph< pair<string, int>, int >(10000);

	numOfAgents = 50;
	start = 1000;
	goal = 8000;

	graphInitialized = false;

}

Map::~Map()
{

}

void Map::Draw(SDL_Renderer * renderer)
{
	/*std::cout << nodeObjects.size() << std::endl;*/
	for (int i = 0; i < nodeObjects.size(); i++)
	{
		nodeObjects.at(i)->Draw(renderer);
	}
	for (int i = 0; i < map.size(); i++)
	{
		map.at(i)->Draw(renderer);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->Draw(renderer);
	}
	player->Draw(renderer);
	/*for (int i = 0; i < map.size(); i++)
	{
		map.at(i)->Draw(renderer);
	}
	for (int i = 0; i < nodeObjects.size(); i++)
	{
		nodeObjects.at(i)->Draw(renderer);
	}*/
	
	
}

void Map::InitializeMap()
{
	SDL_Colour white = SDL_Colour{ 255, 255, 255, 0 };
	player = new Player(300, 400, 50, 50, white);
	SpawnOuterWalls();
	SpawnObstacles();
	InitializeAgents(numOfAgents);
}

void Map::SpawnOuterWalls()
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

// Spawns red Inner Obstacles
void Map::SpawnObstacles()
{
	SDL_Colour red = SDL_Colour{ 220, 0, 0, 0 };
	Obstacle *obstacle1 = new Obstacle(200, 0, StandardWidthAndHeight, window_height/1.5, red);
	Obstacle *obstacle2 = new Obstacle(500, 150, StandardWidthAndHeight, window_height/1.5, red);
	Obstacle *obstacle3 = new Obstacle(800, 100, StandardWidthAndHeight, window_height/1.5, red);
	map.push_back(obstacle1);
	map.push_back(obstacle2);
	map.push_back(obstacle3);
}

//Sets the position of the visual representation of the node objects
void Map::SetNodeRepresentation(int rowWidth, int columnHeight)
{
	for (int i = 0; i < rowWidth; i++)
	{
		for (int y = 0; y < columnHeight; y++)
		{
			SDL_Colour green = SDL_Colour{ 25, 179, 0, 0 };
			NodeObject *nodeObject = new NodeObject(i * 10, y * 10, 5, 5, green);
			nodeObjects.push_back(nodeObject);
		}
	}
}

// Adds nodes to graph
void Map::SetNodes(int rowWidth, int columnHeight)
{
	int count = 0;
	for (int i = 0; i < rowWidth; i++)
	{
		for (int y = 0; y < columnHeight; y++)
		{
			SDL_Point position = SDL_Point{ i * 10, y * 10 };
			graph->addNode(pair<string, int>(std::to_string(count), 0), count, position);
			allWaypoints.push_back(position);
			count++;
		}
	}
}

// Goes through nodes and sets their outgoing arcs
void Map::SetArcs(int rowWidth, int columnHeight)
{
	int standardWeight = 10;

	//std::cout << graph->getSize();
	int size = graph->getSize();

	int x = 0;
	int y = 0;

	for (int i = 0; i < size; i++)
	{
		SDL_Point waypoint = SDL_Point{ graph->nodeArray()[i]->getWaypoint().x, graph->nodeArray()[i]->getWaypoint().y };
		x = waypoint.x / 10 + 1; // column 
		y = waypoint.y / 10 + 1; // row

		int check = x * columnHeight - 1;

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
		if ((i - columnHeight > check - (columnHeight* 2)) && ((check - columnHeight) >=0))
		{
			graph->addArc(i, i - columnHeight, standardWeight);
		}
		// right
		if ((i + columnHeight < check + columnHeight + 1) && ((check + columnHeight) <= (size + 1))  )
		{
			graph->addArc(i, i + columnHeight, standardWeight);
		}
	}
}

// Spawn enemies into level
// Enemies use A*mbush (not here) to search
void Map::SpawnEnemies(int num, SDL_Point start, int width, int height, SDL_Colour colour)
{
	for (int i = 0; i < num; i++)
	{
		Enemy *enemy = new Enemy(start.x, start.y, width, height, colour, i, graph, pCurrent, allWaypoints);
		enemies.push_back(enemy);
	}
	
}

void Map::SetWaypoints(std::vector<SDL_Point> waypoints)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		//enemies.at(i)->SetWaypoints(waypoints.at(i));
	}
}

void Map::RunAStarAmbush(int i)
{
	//graphInitialized = true;
	enemies.at(i)->RunAStarAmbush(i, agents, pCurrent, player->getPosition());
}

void Map::Collisions()
{
	//graph->removeNode(3);
	for (int i = 0; i < map.size(); i++)
	{
		//SDL_IntersectRect(player->getPlayerRect(), map.at(i).)
		for (int y = 0; y < enemies.size(); y++)
		{
			SDL_Rect result;
			SDL_bool collision = SDL_IntersectRect(&map.at(i)->getObstacleRect(), &enemies.at(y)->getRect(), &result);
			if (collision == true)
			{
				if ((enemies.at(y)->getPosition().x + enemies.at(y)->getRect().w) > map.at(i)->getObstaclePosition().x
					&& (enemies.at(y)->getPosition().x + enemies.at(y)->getRect().w) < (map.at(i)->getObstaclePosition().x + map.at(i)->getObstacleRect().w))
				{
					enemies.at(y)->Collision(SDL_Point{ -20, 0 });
				}



				/*if (map.at(i)->getObstacleRect().x > )*/
			//	graph->nodeArray()[y]->SetActive(false);
				/*graph->removeNode(y);*/
			}
			/*}*/
		}
	}
}


void Map::Update()
{
	int speed = 5;
	if (m_eventListener->W == true)
	{
		player->Move(0, -speed);
	}
	if (m_eventListener->A == true)
	{
		player->Move(-speed, 0);
	}
	if (m_eventListener->S == true)
	{
		player->Move(0, speed);
	}
	if (m_eventListener->D == true)
	{
		player->Move(speed, 0);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->Move();
	}

	Collisions();
	//if (graphInitialized == true)
	//{
	//	/*RemoveNodesInObstacles();*/
	//	//graphInitialized = false;
	//}

}

// Initialize agents for A*mbush
void Map::InitializeAgents(int num)
{
	for (int i = 0; i < num; i++)
	{
		theAgent *agent = new theAgent();
		agent->m_currentAgent = i;
		agents.push_back(agent);

	}

	std::cout << "Number of agents initialized: " << agents.size() << std::endl;
}


