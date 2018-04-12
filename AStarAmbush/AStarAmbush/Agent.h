#pragma once
#include <vector>
#include "GraphNode.h"
#include "GraphArc.h"
//
//template <class NodeType, class ArcType> class GraphArc;
//template <class NodeType, class ArcType> class GraphNode;

template<class NodeType, class ArcType>
class Agent
{
private:

	//typedef GraphArc<NodeType, ArcType> Arc;
	//typedef GraphNode<NodeType, ArcType> Node;

public:
	typedef GraphNode<NodeType, ArcType> Node;
	Agent();
	Agent(int currentAgent);
	int m_currentAgent;
	std::vector<Node*> starPath;

	
};

template<class NodeType, class ArcType>
inline Agent<NodeType, ArcType>::Agent()
{

}

template<class NodeType, class ArcType>
inline Agent<NodeType, ArcType>::Agent(int currentAgent)
{
	m_currentAgent = currentAgent;
}
