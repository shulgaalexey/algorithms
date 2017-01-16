#include <iostream>
#include <climits>
#include <vector>
using namespace std;

struct node;

struct edge {
	node *to;
	int w;
	edge(node *t, int _w) : to(t), w(_w) {}
};

struct node {
	char v;
	vector<edge *> adj;
	node *p;
	int d;
	node(char ch) : v(ch), p(NULL), d(INT_MAX / 2) {}
};

node *extract_min(vector<node *> &Q)
{
	size_t min_idx = 0;
	for (size_t i = 1; i < Q.size(); i++)
		if (Q[i]->d < Q[min_idx]->d)
			min_idx = i;
	node *n = Q[min_idx];
	Q.erase(Q.begin() + min_idx);
	return n;
}

void relax(node *n, edge *e)
{
	if (e->to->d > (n->d + e->w)) {
		e->to->d = n->d + e->w;
		e->to->p = n;
	}
}

void dijkstra(const vector<node *> &G, node *s)
{
	s->d = 0;
	vector<node *> Q = G;
	while (!Q.empty()) {
		node *n = extract_min(Q);
		for (size_t i = 0; i < n->adj.size(); i++)
			relax(n, n->adj[i]);
	}
}

void add_edge(const vector<node *> &G, int from, int to, int w)
{
	G[from]->adj.push_back(new edge(G[to], w));
}

int main(void)
{
	const int s = 0, t = 1, x = 2, y = 3, z = 4;
	vector<node *> G(5);
	G[s] = new node('s');
	G[t] = new node('t');
	G[x] = new node('x');
	G[y] = new node('y');
	G[z] = new node('z');

	add_edge(G, s, t, 10);
	add_edge(G, t, x, 1);
	add_edge(G, t, y, 2);
	add_edge(G, y, t, 3);
	add_edge(G, x, z, 4);
	add_edge(G, z, x, 6);
	add_edge(G, z, s, 7);
	add_edge(G, y, z, 2);
	add_edge(G, s, y, 5);

	dijkstra(G, G[s]);

	for (size_t i = 0; i < G.size(); i++) {
		cout << G[i]->v << " (" << G[i]->d << ") parent: ";
		if (G[i]->p)
			cout << G[i]->p->v << endl;
		else
			cout << "NULL" << endl;
	}

	for (size_t i = 0; i < G.size(); i++) {
		for (size_t j = 0; j < G[i]->adj.size(); j++)
			delete G[i]->adj[j];
		delete G[i];
	}

	return 0;
}
