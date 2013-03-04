//============================================================================
// Name        : spotiGraph.cpp
// Author      : Adria Casas - adria.casas.escoda@gmail.com
// Version     : 1.0
// Description : Solution to Spotify Bilateral Projects puzzle
//============================================================================

#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <list>
#include <algorithm>
#include "BiGraph.h"

using namespace std;

#define FRIEND_ID 1009

/**
 *  @brief  Finds new augmenting paths
 *  @param  g  Graph.
 *  @param  m  Current matching.
 *  @param  d  Distance vector used to store the paths.
 *  @return Returns true if a new augmenting path has been found.
**/
bool findAugmentingPaths(const BiGraph &g, map<int, int> &m, map<int, int> &d) {
	int minDist = -1;
	queue<int> q;
	const set<int> &a = g.getA();

	set<int>::const_iterator it;
	for (it = a.begin(); it != a.end(); ++it) {
	    if (m.count(*it) == 0) {
	    	d[*it] = 0;
		    q.push(*it);
	    }
	}

	while (not q.empty()) {
		int a0 = q.front();
		q.pop();
		set<int> adj = g.getAdj(a0);

		for (it = adj.begin(); it != adj.end(); ++it) {
			if (m.count(*it) == 0) {
				//Augmenting path found.
				minDist = d[a0] + 1;
			}
			else if ((minDist == -1) and (d.count(m[*it])==0)) {
				//Continue if augmenting path not found in current layer and node not yet visited.
				d[m[*it]] = d[a0] + 1;
				q.push(m[*it]);
			}
		}
	}
	return minDist != -1;
}

/**
 *  @brief  Modifies the matching using the augmenting Paths stored in d
 *  @param  g  Graph.
 *  @param  m  Current matching.
 *  @param  d  Distance vector used to rebuild the paths.
 *  @return Returns true if a new augmenting path has been applied to the matching.
**/
bool rebuildMatching(int v, const BiGraph &g, map<int, int> &m, map<int, int> &d) {
	const set<int> adj = g.getAdj(v);
	set<int>::const_iterator it;

	for (it = adj.begin(); it != adj.end(); ++it) {
		if(m.count(*it) == 0) {
			//Augmenting path finished
			m[v] = *it;
			m[*it] = v;
			return true;
		}

		int match = m[*it];
		if ((d.count(match)==1) and (d[match] == (d[v]+1)) and rebuildMatching(match, g, m, d)) {
			m[v] = *it;
			m[*it] = v;
			return true;
		}
	}
	// Mark d as visited
	d[v] = -1;
	return false;
}

/**
 *  @brief  Finds the adjacent vertexes using edges.
 *  @param  g  Set of vertexes.
 *  @param  d  Set of edges.
 *  @return Returns set of adjacent vertexes.
**/
set<int> getAdjFromMatch(const set<int> &vertexs, const map<int, int> &edges) {
	set<int> adj;
	set<int>::const_iterator it;

	map<int, int>::const_iterator edge;
	map<int, int>::const_iterator end = edges.end();

	for (it = vertexs.begin(); it != vertexs.end(); ++it) {
		if ((edge = edges.find(*it)) != end) {
			adj.insert(edge->second);
		}
	}
	return adj;
}

/**
 *  @brief  Finds the adjacent vertexes using edges.
 *  @param  g  Set of vertexes.
 *  @param  d  Set of edges.
 *  @return Returns set of adjacent vertexes.
**/
set<int> getAdjFromNoMatch(const set<int> &vertexs, const map<int, set<int> > &edges) {
	set<int> adj;
	set<int>::const_iterator it;

	map<int, set<int> >::const_iterator vSet;
	map<int, set<int> >::const_iterator end = edges.end();

	for (it = vertexs.begin(); it != vertexs.end(); ++it) {
		if ((vSet = edges.find(*it)) != end) {

			set<int>::const_iterator it2;
			for (it2 = vSet->second.begin(); it2 != vSet->second.end(); ++it2) {
				adj.insert(*it2);
			}
		}
	}
	return adj;
}

/**
 *  @brief  Finds the difference between two sets of edges (a-b)
 *  @param  a  Set of edges.
 *  @param  d  Set of edges.
 *  @return Returns the result of a-b.
**/
map<int, set<int> > getDifference(const map<int, set<int> > &a, const map<int, int> &b) {
	map<int, set<int> > diff = map<int, set<int> >(a);
	map<int, int>::const_iterator it;

	map<int, set<int> >::iterator edgeSet;

	for (it = b.begin(); it != b.end(); ++it) {
		if ((edgeSet = diff.find(it->first)) != diff.end()) {
			edgeSet->second.erase(it->second);
		}
	}
	return diff;
}

/**
 *  @brief  Finds the minimum Cover of g given its maximum matching using König's theorem.
 *  @param  g  Graph.
 *  @param  m  Maximum matching of g.
 *  @return Returns the list of vertexes in the minimum cover.
**/
list<int> minCoverFromMatching(const BiGraph &g, const map<int, int> &m) {
	//Temporal vertex set used to build the minCover.
	set<int> t;

	//Initialize minCover
	set<int> minCover;
	const set<int> a = g.getA();
	const set<int> b = g.getB();

	//Edges not in matching.
	map<int, set<int> > no_m = getDifference(g.getEdges(), m);

	//Build t.
	set<int>::const_iterator it;
	for (it = a.begin(); it != a.end(); ++it) {
		if (m.count(*it) == 0) {
			t.insert(*it);
		}
	}

	set<int> new_a = t;
	set<int> new_b;
	unsigned int size;

	do {
		size = t.size();

		new_b = getAdjFromNoMatch(new_a, no_m);
		t.insert(new_b.begin(), new_b.end());

		new_a = getAdjFromMatch(new_b, m);
		t.insert(new_a.begin(), new_a.end());

	} while (size != t.size());

	//Build the minCover using t.
	list<int> res_a = list<int>(a.size());
	list<int>::iterator end_a = set_difference(a.begin(), a.end(), t.begin(), t.end(), res_a.begin());

	list<int> res_b = list<int>(max(b.size(), t.size()));
	list<int>::iterator end_b = set_intersection(b.begin(), b.end(), t.begin(), t.end(), res_b.begin());

	list<int> res = list<int>(res_a.size()+res_b.size());
	list<int>::iterator end_res = set_union(res_a.begin(), end_a, res_b.begin(), end_b, res.begin());

	return list<int>(res.begin(), end_res);
}

/**
 *  @brief  Finds the maximum matching of g using Hopcroft–Karp algorithm.
 *  @param  g  Graph.
 *  @return Returns the set of edges in the maximum matching.
**/
map<int, int> maxMatching(const BiGraph &g) {
	map<int, int> m;
	map<int, int> d;

	while (findAugmentingPaths(g, m, d)) {
 		//augmenting path found.
 		set<int>::const_iterator it;
		const set<int> a = g.getA();
		for (it = a.begin(); it != a.end(); ++it) {
			if (m.count(*it) == 0) {
				//Is a free vertex of partition A.
				rebuildMatching(*it, g, m, d);
			}
		}
		d.clear();
	}
	return m;
}

/**
 *  @brief  Finds the minimum cover of g.
 *  @param  g  Graph.
 *  @return Returns the list of vertexes in the minimum cover.
**/
list<int> minCover(const BiGraph &g) {
	map<int, int> m = maxMatching(g);
	return minCoverFromMatching(g, m);
}

int main() {
	BiGraph g = BiGraph(cin);

	list<int> minC = minCover(g);
	if (g.removeVertex(FRIEND_ID)) {
		list<int> minC_withoutFriend = minCover(g);

		if (minC_withoutFriend.size() < minC.size()) {
			minC_withoutFriend.push_back(FRIEND_ID);
			minC = minC_withoutFriend;
		}
	}

	cout << minC.size() << endl;
	list<int>::const_iterator it;
	for (it = minC.begin(); it != minC.end(); ++it) {
		cout << *it << endl;
	}

	return 0;
}
