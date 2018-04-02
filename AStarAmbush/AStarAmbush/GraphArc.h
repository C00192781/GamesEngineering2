#ifndef GRAPHARC_H
#define GRAPHARC_H

#include "GraphNode.h"

// -------------------------------------------------------
// Name:        GraphArc
// Description: This is the arc class. The arc class
//              points to a graph node, and contains a 
//              weight.
// -------------------------------------------------------
template<class NodeType, class ArcType>
class GraphArc {
private:

	// -------------------------------------------------------
	// Description: pointer to the node that the arc points to
	// -------------------------------------------------------
	GraphNode<NodeType, ArcType>* m_pNode;

	// -------------------------------------------------------
	// Description: Weight of the arc
	// -------------------------------------------------------
	ArcType m_weight;

public:

	// Accessor functions
	GraphNode<NodeType, ArcType>* node() const {
		return m_pNode;
	}

	ArcType weight() const {
		return m_weight;
	}

	// Manipulator functions
	void setNode(GraphNode<NodeType, ArcType>* pNode) {
		m_pNode = pNode;
	}

	void setWeight(ArcType weight) {
		m_weight = weight;
	}

};

#endif
