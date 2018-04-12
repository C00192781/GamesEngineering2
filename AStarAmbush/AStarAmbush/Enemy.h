#pragma once

#ifndef ENEMY_H
#define ENEMY_H


#include "SDL.h"
#include <vector>
#include <string>
#include "Graph.h"
#include "GraphArc.h"
#include "GraphNode.h"
#include <algorithm>

using namespace std;

#define window_width 1080
#define window_height 720

#define StandardWidthAndHeight 50

typedef GraphArc<std::string, int> Arc;
typedef GraphNode<pair<std::string, int>, int> Node;
typedef Agent<pair<std::string, int>, int> theAgent;

class Enemy
{
public:
	Enemy(int x, int y, int w, int h, SDL_Colour col, int tag, Graph<pair<string,int>, int> *graph, Node *pCurrent, std::vector<SDL_Point> allWaypoints);
	~Enemy();

	void Draw(SDL_Renderer * renderer);
	void Move();
	void SetTarget(SDL_Point target);
	void SetWaypoints(std::vector<SDL_Point> waypoints);
	void RunAStarAmbush(int agent, std::vector<theAgent*> agents, Node *pCurrent, SDL_Point playerPos);
	int searchNearestWaypoint(SDL_Point position);




private:
	SDL_Rect rect;
	SDL_Point position;
	SDL_Colour colour;

	int xPos;
	int yPos;
	int width;
	int height;

	int xSpeed;
	int ySpeed;

	int agentTag;
	SDL_Point m_target;
	std::vector<SDL_Point> pathWaypoints;
	std::vector<SDL_Point> everyWaypoint;

	Graph< pair<string, int>, int > *graph;
	Node *current;

	bool initialized = false;

	


};
#endif
