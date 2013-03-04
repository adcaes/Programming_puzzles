#ifndef BIGRAPH_H_
#define BIGRAPH_H_

#include <iostream>
#include <map>
#include <set>

using namespace std;

#define FRIEND_ID 1009

class BiGraph {
private:
	set<int> A;
	set<int> B;
	map<int, set<int> > edges;

public:
	BiGraph(istream& s);

	const set<int>& getA() const;
	const set<int>& getB() const;
	const map<int, set<int> >& getEdges() const;
	const set<int>& getAdj(int v) const;

	bool removeVertex(int v);
};

#endif /* BIGRAPH_H_ */
