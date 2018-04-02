#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <queue>

using namespace std;

template <class NodeType, class ArcType> class GraphArc;
template <class NodeType, class ArcType> class GraphNode;
template <class NodeType, class ArcType> class Agent;


template<class NodeType, class ArcType>
class NodeSearchCostComparer
{
public:
	typedef GraphNode<NodeType, ArcType> Node;
	bool operator() (Node * n1, Node * n2)
	{
		pair<string, int> p1 = n1->data();
		pair<string, int> p2 = n2->data();
		return p1.second > p2.second;
	}
};



template<class NodeType, class ArcType>
class NodeSearchCostComparer2
{
public:
	typedef GraphNode<NodeType, ArcType> Node;
	bool operator() (Node * n1, Node * n2)
	{
		int p1 = n1->getEstimate() + n1->data().second;
		int p2 = n2->getEstimate() + n2->data().second;
		return p1 > p2;
	}
};



// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    This is the graph class, it contains all the
//                  nodes.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
class Graph {
private:

    // typedef the classes to make our lives easier.
    typedef GraphArc<NodeType, ArcType> Arc;
    typedef GraphNode<NodeType, ArcType> Node;
	typedef Agent<NodeType, ArcType> Agent;

// ----------------------------------------------------------------
//  Description:    A container of all the nodes in the graph.
// ----------------------------------------------------------------

	//std::vector<Node *> m_nodes;

	// An array of all the nodes in the graph.
	Node** m_pNodes;

	// the maximum number of nodes in the graph.
	int m_maxNodes;

	


public:           
    // Constructor and destructor functions
    Graph(int size);
    ~Graph();

    // Accessors
    Node** nodeArray() const {
		return m_pNodes;
    }

    // Public member functions.
    bool addNode( NodeType data, int index );
    void removeNode( int index );
    bool addArc( int from, int to, ArcType weight );
    void removeArc( int from, int to );
    Arc* getArc( int from, int to );        
    void clearMarks();
    void depthFirst( Node* pNode, void (*pProcess)(Node*) );
    void breadthFirst( Node* pNode, void (*pProcess)(Node*) );
	
	void ucs(Node* pStart, Node* pDest, std::vector<Node *>& path);
	void aStar(Node* pStart, Node* pDest,
		std::vector<Node *>& path);
	void aStarAmbushInitialize(Node * pStart, std::priority_queue < Node *, vector<Node *>, NodeSearchCostComparer2<NodeType, ArcType>> *nodeQueue);
	void aStarAmbush (Node * pStart, Node* pDest, std::vector<Agent *>& agents, Agent * agent);
	int calculateDegree(Node* currentNode, std::vector<Agent *> agents, Agent * currentAgent);

	/*void UCS*/
};

// ----------------------------------------------------------------
//  Name:           Graph
//  Description:    Constructor, this constructs an empty graph
//  Arguments:      The maximum number of nodes.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::Graph(int size) : m_maxNodes(size) {
	int i;
	m_pNodes = new Node *[m_maxNodes];
	// go through every index and clear it to null (0)
	for (i = 0; i < m_maxNodes; i++) {
		m_pNodes[i] = 0;
	}

	
}

// ----------------------------------------------------------------
//  Name:           ~Graph
//  Description:    destructor, This deletes every node
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
Graph<NodeType, ArcType>::~Graph() {
   for( int index = 0; index < m_maxNodes; index++ ) {
        if( m_pNodes[index] != 0 ) {
			delete m_pNodes[index];
        }
   }
}

// ----------------------------------------------------------------
//  Name:           addNode
//  Description:    This adds a node at a given index in the graph.
//  Arguments:      The first parameter is the data to store in the node.
//                  The second parameter is the index to store the node.
//  Return Value:   true if successful
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addNode( NodeType data, int index ) {
   bool nodeNotPresent = false;
   // find out if a node does not exist at that index.
   if (m_pNodes[index] == 0) {
      nodeNotPresent = true;
      // create a new node, put the data in it, and unmark it.
	  m_pNodes[index] = new Node;
	  m_pNodes[index]->setData(data);
	  m_pNodes[index]->setMarked(false);

	  

    }
        
    return nodeNotPresent;
}

// ----------------------------------------------------------------
//  Name:           removeNode
//  Description:    This removes a node from the graph
//  Arguments:      The index of the node to return.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeNode( int index ) {
     // Only proceed if node does exist.
     if(m_pNodes[index] != 0) {
         // now find every arc that points to the node that
         // is being removed and remove it.        
         Arc* arc;

         // loop through every node
         for( int node = 0; node < m_maxNodes; node++ ) {
              // if the node is valid...
              if(m_pNodes[node] != 0) {
                  // see if the node has an arc pointing to the current node.
                  arc = m_pNodes[node]->getArc(m_pNodes[index] );
              }
              // if it has an arc pointing to the current node, then
              // remove the arc.
              if( arc != 0 ) {
                  removeArc( node, index );
              }
         }
        

        // now that every arc pointing to the current node has been removed,
        // the node can be deleted.
        delete m_pNodes[index];
		m_pNodes[index] = 0;
    }
}

// ----------------------------------------------------------------
//  Name:           addArd
//  Description:    Adds an arc from the first index to the 
//                  second index with the specified weight.
//  Arguments:      The first argument is the originating node index
//                  The second argument is the ending node index
//                  The third argument is the weight of the arc
//  Return Value:   true on success.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
bool Graph<NodeType, ArcType>::addArc( int from, int to, ArcType weight ) {
     bool proceed = true; 
     // make sure both nodes exist.
     if( m_pNodes[from] == 0 || m_pNodes[to] == 0 ) 
	 {
         proceed = false;
     }
        
     // if an arc already exists we should not proceed
     if(m_pNodes[from]->getArc(m_pNodes[to] ) != 0 ) {
         proceed = false;
     }

     if (proceed == true) {
        // add the arc to the "from" node.
		 m_pNodes[from]->addArc(m_pNodes[to], weight );
     }
        
     return proceed;
}

// ----------------------------------------------------------------
//  Name:           removeArc
//  Description:    This removes the arc from the first index to the second index
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::removeArc( int from, int to ) {
     // Make sure that the node exists before trying to remove
     // an arc from it.
     bool nodeExists = true;
     if( m_pNodes[from] == 0 || m_pNodes[O] == 0 ) 
	 {
         nodeExists = false;
     }

     if (nodeExists == true) 
	 {
        // remove the arc.
		 m_pNodes[from]->removeArc(m_pNodes[to]);
     }
}


// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    Gets a pointer to an arc from the first index
//                  to the second index.
//  Arguments:      The first parameter is the originating node index.
//                  The second parameter is the ending node index.
//  Return Value:   pointer to the arc, or 0 if it doesn't exist.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
GraphArc<NodeType, ArcType>* Graph<NodeType, ArcType>::getArc( int from, int to ) {
     Arc* arc = 0;
     // make sure the to and from nodes exist
     if( m_pNodes[from] != 0 && m_pNodes[to] != 0 ) {
         arc = m_pNodes[from]->getArc(m_pNodes[to]);
     }
                
     return arc;
}


// ----------------------------------------------------------------
//  Name:           clearMarks
//  Description:    This clears every mark on every node.
//  Arguments:      None.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::clearMarks() {
     for( int index = 0; index < m_maxNodes; index++ ) {
          if(m_pNodes[index] != 0) 
		  {
			  m_pNodes[index]->setMarked(false);
          }
     }
}


// ----------------------------------------------------------------
//  Name:           depthFirst
//  Description:    Performs a depth-first traversal on the specified 
//                  node.
//  Arguments:      The first argument is the starting node
//                  The second argument is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::depthFirst( Node* node, void (*process)(Node*) ) {
     if( nullptr != node ) {
           // process the current node and mark it
           pProcess( node );
           node->setMarked(true);

		   // go through each connecting node
		   list<Arc>::iterator iter = pNode->arcList().begin();
		   list<Arc>::iterator endIter = pNode->arcList().end();
        
		   for( ; iter != endIter; ++iter) 
		   {
			    // process the linked node if it isn't already marked.
                if ( (*iter).node()->marked() == false ) 
				{
                   depthFirst( (*iter).node(), process);
                }            
           }
     }
}


// ----------------------------------------------------------------
//  Name:           breadthFirst
//  Description:    Performs a depth-first traversal the starting node
//                  specified as an input parameter.
//  Arguments:      The first parameter is the starting node
//                  The second parameter is the processing function.
//  Return Value:   None.
// ----------------------------------------------------------------
template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::breadthFirst( Node* node, void (*process)(Node*) ) {
   if( node != 0 ) {
	  queue<Node*> nodeQueue;        
	  // place the first node on the queue, and mark it.
      nodeQueue.push( node );
      node->setMarked(true);

      // loop through the queue while there are nodes in it.
      while( nodeQueue.size() != 0 ) {
         // process the node at the front of the queue.
         process( nodeQueue.front() );

         // add all of the child nodes that have not been 
         // marked into the queue
		 list<Arc>::const_iterator iter = nodeQueue.front()->arcList().begin();
		 list<Arc>::const_iterator endIter = nodeQueue.front()->arcList().end();
         
		 for( ; iter != endIter; iter++ ) 
		 {
              if ( (*iter).node()->marked() == false) 
			  {
				 // mark the node and add it to the queue.
                 (*iter).node()->setMarked(true);
				 /////////////////***********************next 2 lines
				/* std::cout << (*iter).node()->data() << " Previous:" << (*iter).node()->getPrevious()->data() << std::endl;
				 (*iter).node()->setMarked(true);*/
                 nodeQueue.push( (*iter).node() );
              }
         }

         // dequeue the current node.
         nodeQueue.pop();
      }
   }  
}


template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::ucs(Node* pStart, Node* pDest, std::vector<Node *>& path)
{
	std::priority_queue < Node *, vector<Node *>, NodeSearchCostComparer<NodeType, ArcType>> nodeQueue;
	if (pStart != 0)
	{	
		// insert starting node into the queue
		nodeQueue.push(pStart);
		
		// setting the initial values of all of the nodes
		for (int i = 0; i < m_maxNodes; i++)
		{
			//m_pNodes[i]->setMarked(false);
			auto data = m_pNodes[i]->data();
			// set the weight to an infinite value to start off with
			data.second = std::numeric_limits<int>::max() - 100000;
			m_pNodes[i]->setData(data);
		}

		//set the starting node weight to 0
		pStart->setData(pair<string, int>(pStart->data().first, 0));
		//set is being marked/visited
		//pStart->setMarked(true);
	}



	// while the node queue size is not 0 and we haven't reached our Goal Node yet
	while (nodeQueue.size() != 0 && nodeQueue.top() != pDest)
	{
		//set up iterators
		list<Arc>::const_iterator iter = nodeQueue.top()->arcList().begin();
		list<Arc>::const_iterator endIter = nodeQueue.top()->arcList().end();

		// for each iteration though the nodes
		for (; iter != endIter; iter++)
		{
			// if the current node is not the highest priority node - THEN WE KNOW TO START ADDING UP DISTANCE
			if ((*iter).node() != nodeQueue.top())
			{
				// EACH TIME WE ITERATE THROUGH THE NODES WE ADD THE DISTANCE
				// distance = the distance of the current node + the distance added up so far 
				int distance = nodeQueue.top()->data().second + iter->weight();


				/////// FOR FINDING SHORTEST PATH
				// if the distance is less than the weight of the current node, i.e. we've found a shorter path
				if (distance < (*iter).node()->data().second)
				{
					// set the current node's values - same name, the shorter/new distance
					(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, distance));
					// set the previous node as being the node with the shortest path
					(*iter).node()->setPrevious((nodeQueue.top()));
				}


				///////// FOR MARKING
				// if the node has not been marked
				if ((*iter).node()->marked() == false)
				{
					//(*iter).node()->setPrevious((nodeQueue.top()));
					// mark it as being true
					(*iter).node()->setMarked(true);
					// push the current node to the queue
					nodeQueue.push((*iter).node());
				}
			}
		}
		//////// REMOVE NODE
		// remove the node from the front of the queue
		nodeQueue.pop();
	}
}


template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::aStar(Node* pStart, Node* pDest, std::vector<Node *>& path)
{
	std::vector<Node*> starPath;

	ucs(pDest, pStart, starPath);

	
	std::priority_queue < Node *, vector<Node *>, NodeSearchCostComparer2<NodeType, ArcType>> nodeQueue;


	if (pStart != 0)
	{
		// insert starting node into the queue
		nodeQueue.push(pStart);
		
		
		// setting the initial values of all of the nodes
		for (int i = 0; i < m_maxNodes; i++)
		{
			// ESTIMATE, i.e. g(n)
			m_pNodes[i]->setEstimate(m_pNodes[i]->data().second*0.9);
			auto data = m_pNodes[i]->data();
			// set the weight to an infinite value to start off with
			data.second = std::numeric_limits<int>::max() - 100000;
			m_pNodes[i]->setData(data);
			m_pNodes[i]->setMarked(false);
		}

		//set the starting node weight to 0
		pStart->setData(pair<string, int>(pStart->data().first, 0));
		//set as being marked/visited
		pStart->setMarked(true);

	}


	// while the node queue size is not 0 and we haven't reached our Goal Node yet
	while (nodeQueue.size() != 0 && nodeQueue.top() != pDest)
	{
		//set up iterators
		list<Arc>::const_iterator iter = nodeQueue.top()->arcList().begin();
		list<Arc>::const_iterator endIter = nodeQueue.top()->arcList().end();

		// for each iteration though the nodes
		for (; iter != endIter; iter++)
		{
			// if the current node is not the highest priority node - THEN WE KNOW TO START ADDING UP DISTANCE
			if ((*iter).node() != nodeQueue.top())
			{			
				int distance = nodeQueue.top()->data().second + iter->weight();
				///// FOR FINDING SHORTEST PATH
				 ////if the distance is less than the weight of the current node, i.e. we've found a shorter path
				if (distance < (*iter).node()->data().second)
				{
					/// set the current node's values - same name, the shorter/new distance
					(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, distance));
					 ///set the previous node as being the node with the shortest path
					(*iter).node()->setPrevious((nodeQueue.top()));
				}


				///////// FOR MARKING
				// if the node has not been marked
				if ((*iter).node()->marked() == false)
				{
					//(*iter).node()->setPrevious((nodeQueue.top()));
					// mark it as being true
					(*iter).node()->setMarked(true);
					// push the current node to the queue
					nodeQueue.push((*iter).node());
				}
			}
		}
		//////// REMOVE NODE
		// remove the node from the front of the queue
		nodeQueue.pop();
	}

}

template<class NodeType, class ArcType>
inline void Graph<NodeType, ArcType>::aStarAmbushInitialize(Node * pStart, std::priority_queue < Node *, vector<Node *>, NodeSearchCostComparer2<NodeType, ArcType>> *nodeQueue)
{
	if (pStart != 0)
	{
		// insert starting node into the queue
		nodeQueue->push(pStart);

		// setting the initial values of all of the nodes
		for (int i = 0; i < m_maxNodes; i++)
		{
			// ESTIMATE, i.e. g(n)
			m_pNodes[i]->setEstimate(m_pNodes[i]->data().second*0.9);
			auto data = m_pNodes[i]->data();
			// set the weight to an infinite value to start off with
			data.second = std::numeric_limits<int>::max() - 100000;
			m_pNodes[i]->setData(data);
			m_pNodes[i]->setMarked(false);
		}

		//set the starting node weight to 0
		pStart->setData(pair<string, int>(pStart->data().first, 0));
		//set as being marked/visited
		pStart->setMarked(true);
	}
	std::cout << std::endl;
	std::cout << "A* Ambush initialized" << std::endl;
	std::cout << std::endl;
}


template<class NodeType, class ArcType>
void Graph<NodeType, ArcType>::aStarAmbush(Node* pStart, Node* pDest, std::vector<Agent *>& agents, Agent * agent)
{
	//std::vector<Node*> starPath;
	for (int i = 0; i < m_maxNodes; i++)
	{
		m_pNodes[i]->setPrevious(nullptr);
		m_pNodes[i]->setData(pair<string, int>(m_pNodes[i]->data().first, std::numeric_limits<int>::max() - 100000));
		m_pNodes[i]->setEstimate(m_pNodes[i]->data().second);
		m_pNodes[i]->setMarked(false);
	}

	ucs(pDest, pStart, agent->starPath);

	std::priority_queue < Node *, vector<Node *>, NodeSearchCostComparer2<NodeType, ArcType>> nodeQueue;

	aStarAmbushInitialize(pStart, &nodeQueue);


	// while the node queue size is not 0 and we haven't reached our Goal Node yet
	while (nodeQueue.size() != 0 && nodeQueue.top() != pDest)
	{
		//set up iterators
		list<Arc>::const_iterator iter = nodeQueue.top()->arcList().begin();
		list<Arc>::const_iterator endIter = nodeQueue.top()->arcList().end();

		// for each iteration though the nodes
		for (; iter != endIter; iter++)
		{
			// if the current node is not the highest priority node - THEN WE KNOW TO START ADDING UP DISTANCE
			if ((*iter).node() != nodeQueue.top())
			{
				//int distance = nodeQueue.top()->data().second + iter->weight();
				// ***************************
				int distance = nodeQueue.top()->data().second + iter->weight() * calculateDegree((*iter).node(), agents, agent) * calculateDegree((*iter).node(), agents, agent);
				
				
				
				///// FOR FINDING SHORTEST PATH
				////if the distance is less than the weight of the current node, i.e. we've found a shorter path
				if (distance < (*iter).node()->data().second)
				{
					// set the current node's values - same name, the shorter/new distance
					(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, distance));
					//set the previous node as being the node with the shortest path
					(*iter).node()->setPrevious((nodeQueue.top()));
				}


				///////// FOR MARKING
				// if the node has not been marked/visited
				if ((*iter).node()->marked() == false)
				{
					(*iter).node()->setPrevious((nodeQueue.top()));
					// mark it as being true
					(*iter).node()->setMarked(true);
					// push the current node to the queue
					nodeQueue.push((*iter).node());
				}

				if ((*iter).node() == pDest)
				{
					if (distance <= (*iter).node()->data().second)
					{
						// set the current node's values - same name, the shorter/new distance
						(*iter).node()->setData(pair<string, int>((*iter).node()->data().first, distance));
						//set the previous node as being the node with the shortest path
						(*iter).node()->setPrevious((nodeQueue.top()));
												
						Node* node = (*iter).node();
						//starPath.push_back((*iter).node());
						agent->starPath.push_back(node);
						
						// Retrieve pointer to the previous node 
						while (pStart != node)
						{
							node = node->getPrevious();
							// Push this to the path vector
							//starPath.push_back(node);
							agent->starPath.push_back(node);
						}
					}
				}

			}
		}
		//////// REMOVE NODE
		// remove the node from the front of the queue
		nodeQueue.pop();
	}

}

template<class NodeType, class ArcType>
inline int Graph<NodeType, ArcType>::calculateDegree(Node* currentNode, std::vector<Agent *> agents, Agent * currentAgent)
{
	// variables:
	// - path
	// - node in question
	// - current agent
	// - counter

	int counter;
	counter = 1;

	// for loop that goes through all agents
	//   for loop that goes through all nodes in the path
	//     check if the current node is equal to one of those nodes in the path
	//        increment counter
	// return counter


	for (int i = 0; i < agents.size(); i++)
	{
		for (int y = 0; y < agents.at(i)->starPath.size(); y++)
		{
			if (currentNode == agents.at(i)->starPath.at(y))
			{
				
				if (agents.at(i)->m_currentAgent != (*currentAgent).m_currentAgent)
				{

					counter++;
				}
			}
		}
	
	}
	//std::cout << counter << std::endl;
	return counter;
	//return 0;
	
}


#include "GraphNode.h"
#include "GraphArc.h"
#include "Agent.h"


#endif
