#include "BiGraph.h"

/**
 *  @brief  Constructor. Creates a new bipartite graph with the set of edges read from s.
 *  @param  s  Input stream where the set of edges are read.
**/
BiGraph::BiGraph(istream& s) {
	int num_pairs, i, a, b;
	cin >> num_pairs;

	//Build a graph with the employee pairs
	for (i=0; i<num_pairs; ++i) {
		s >> a >> b;
		A.insert(a);
		B.insert(b);

		edges[a].insert(b);
		edges[b].insert(a);
	}
}

/**
 *  @return The set of vertexes of partition A of the %graph.
**/
const set<int>& BiGraph::getA() const {
	return A;
}

/**
 *  @return The set of vertexes of partition B of the %graph.
**/
const set<int>& BiGraph::getB() const {
	return B;
}

/**
 *  @return The set of edges of the %graph.
**/
const map<int, set<int> >& BiGraph::getEdges() const {
	return edges;
}

/**
 *  @brief  Finds the set of vertexes adjacent to v in the %graph.
 *  @param  v  Vertex.
 *  @return The set of vertexes adjacent to v.
**/
const set<int>& BiGraph::getAdj(int v) const {
	return edges.find(v)->second;
}

/**
 *  @brief  Remove a vertex from the %graph.
 *  @param  v  Vertex to remove.
 *  @return True if the vertex was in the graph and false otherwise.
**/
bool BiGraph::removeVertex(int v) {
	if (A.count(v) != 0 or B.count(v) != 0) {
		//erase edges
		map<int, set<int> >::const_iterator vSet = edges.find(v);
		set<int>::const_iterator it;
		for (it = vSet->second.begin(); it != vSet->second.end(); ++it) {
			edges.find(*it)->second.erase(v);
		}

		//erase vertex
		A.erase(v);
		B.erase(v);

		return true;
	}
	return false;
}

