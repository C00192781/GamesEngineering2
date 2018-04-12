#include "Enemy.h"

Enemy::Enemy(int x, int y, int w, int h, SDL_Colour col, int tag, Graph< pair<string, int>, int > *passedGraph, Node *pCurrent, std::vector<SDL_Point> allWaypoints)
{
	xPos = x;
	yPos = y;
	width = w;
	height = h;
	colour = col;

	rect = { xPos, yPos, width, height };
	xSpeed = 0;
	ySpeed = 0;
	graph = passedGraph;
	current = pCurrent;

	initialized = false;
	everyWaypoint = allWaypoints;
	
}

Enemy::~Enemy()
{

}

void Enemy::Draw(SDL_Renderer * renderer)
{
	SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
	SDL_RenderFillRect(renderer, &rect);
}

void Enemy::Move()
{
	if (initialized == true)
	{
		if (rect.x < m_target.x)
		{
			rect.x+=2;
		}
		if (rect.x > m_target.x)
		{
			rect.x-=2;
		}
		if (rect.y < m_target.y)
		{
			rect.y+=2;
		}
		if (rect.y > m_target.y)
		{
			rect.y-=2;
		}


		if (rect.x == m_target.x && rect.y == m_target.y)
		{
			if (pathWaypoints.size() > 0)
			{
				std::reverse(pathWaypoints.begin(), pathWaypoints.end());
				pathWaypoints.pop_back();
				if (pathWaypoints.size() > 0)
				{
					std::reverse(pathWaypoints.begin(), pathWaypoints.end());
					SetTarget(pathWaypoints.front());
				}
			}
		}
	}
}

void Enemy::SetTarget(SDL_Point target)
{
	m_target = target;
}

void Enemy::SetWaypoints(std::vector<SDL_Point> waypoints)
{
	//m_waypoints = waypoints;
}

void Enemy::RunAStarAmbush(int agent, std::vector<theAgent*> agents, Node *pCurrent, SDL_Point playerPos)
{
	pathWaypoints.clear();

	int start = searchNearestWaypoint(SDL_Point{ rect.x, rect.y });
	int goal = searchNearestWaypoint(playerPos);

	graph->aStarAmbush(graph->nodeArray()[start], graph->nodeArray()[goal], agents, agents.at(agent));
	pCurrent = graph->nodeArray()[goal];
	
	if (agents.at(agent)->starPath.size() > 0)
	{
		agents.at(agent)->starPath.pop_back();

		for (int index = 0; index < agents.at(agent)->starPath.size(); index++)
		{
			if (agents.at(agent)->starPath.at(index) == graph->nodeArray()[goal])
			{
				std::cout << "start" << std::endl;
			}
			std::cout << agents.at(agent)->starPath.at(index)->data().first << " " << agents.at(agent)->starPath.at(index)->data().second << std::endl;
			pathWaypoints.push_back(agents.at(agent)->starPath.at(index)->getWaypoint());
			/*std::cout << agents.at(agent)->starPath.at(index)->WA*/
		}

		std::reverse(pathWaypoints.begin(), pathWaypoints.end());
		/*for (int i = 0; i < m_waypoints.size(); i++)
		{
			std::cout << "waypoints: " << m_waypoints.at(i).x << " " << m_waypoints.at(i).y <<std::endl;
		}*/
		std::cout << "waypoints: " << pathWaypoints.front().x << " " << pathWaypoints.front().y << std::endl;
		SetTarget(pathWaypoints.front());
		initialized = true;
	}
	
}

int Enemy::searchNearestWaypoint(SDL_Point position)
{
	float differenceValue = std::numeric_limits<int>::max() - 10000;
	int differenceIndex;

	for (int i = 0; i < everyWaypoint.size(); i++)
	{
		SDL_Point difference;
		difference.x = position.x - everyWaypoint.at(i).x;
		difference.y = position.y - everyWaypoint.at(i).y;

		float diff = sqrtf((difference.x*difference.x) + (difference.y*difference.y));
		if (diff < differenceValue)
		{
			differenceValue = diff;
			differenceIndex = i;
		}
	}

	//return everyWaypoint.at(differenceIndex);
	return differenceIndex;
}

SDL_Point Enemy::getPosition()
{
	return SDL_Point{ xPos, yPos };
}

SDL_Rect Enemy::getRect()
{
	return rect;
}

void Enemy::Collision(SDL_Point offset)
{
	rect.x += offset.x;
	rect.y += offset.y;
}


