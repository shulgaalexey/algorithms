#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class node;

class edge {
public:
	node *from;
	node *to;
	int w;
	edge(node *f, node *t, int _w) : from(f), to(t), w(_w) {}
};

class node {
public:
	char v;
	node *p;
	int d;
	node(char ch) : v(ch), p(NULL), d(INT_MAX) {}
};

void pacify(edge *e)
{
	if (e->to->d > (e->from->d + e->w)) {
		e->to->d = e->from->d + e->w;
		e->to->p = e->from;
	}
}

bool single_source_shortest_path(const vector<node *> &V, const vector<edge *> &E, node *s)
{
	s->d = 0;

	for (int i = 0; i < (int(V.size()) - 1); i++)
		for (size_t j = 0; j < E.size(); j++)
			pacify(E[j]);

	for (size_t i = 0; i < E.size(); i ++) {
		edge *e = E[i];
		if (e->to->d > (e->from->d + e->w))
			return false;
	}

	return true;
}

int main(void)
{
	int S = 0, T = 1, X = 2, Y = 3, Z = 4;

	vector<node *> V(5);
	V[S] = new node('s');
	V[T] = new node('t');
	V[X] = new node('x');
	V[Y] = new node('y');
	V[Z] = new node('z');

	vector<edge *> E;
	E.push_back(new edge(V[S], V[T], 6));
	E.push_back(new edge(V[S], V[Y], 7));
	E.push_back(new edge(V[T], V[X], 5));
	E.push_back(new edge(V[T], V[Z], -4));
	E.push_back(new edge(V[T], V[Y], 8));
	E.push_back(new edge(V[X], V[T], -2));
	E.push_back(new edge(V[Y], V[X], -3));
	E.push_back(new edge(V[Y], V[Z], 9));
	E.push_back(new edge(V[Z], V[S], 2));
	E.push_back(new edge(V[Z], V[X], 7));

	const bool ret = single_source_shortest_path(V, E, V[S]);
	cout << ret << endl;

	for (size_t i = 0; i < V.size(); i++)
		if (V[i]->p)
			cout << V[i]->v << " has parent: " << V[i]->p->v << endl;

	for (size_t i = 0; i < V.size(); i++)
		delete V[i];
	for (size_t i = 0; i < E.size(); i++)
		delete E[i];
	return 0;
}
