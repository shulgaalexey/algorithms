#include <iostream>
#include <vector>
#include <list>
#include <climits>
using namespace std;

struct node;

struct edge {
	node *to;
	int w;
	edge(node *t, int _W) : to(t), w(_W) {}
};

struct node {
	char v;
	vector<edge *> adj;
	node *p;
	int d;
	bool visited;
	node(char ch) : v(ch), p(NULL), d(INT_MAX / 2), visited(false) {}
};

void dfs_visit(node *n, list<node *> &l)
{
	n->visited = true;
	for (size_t i = 0; i < n->adj.size(); i++) {
		node *cur = n->adj[i]->to;
		if (!cur->visited) {
			cur->p = n;
			dfs_visit(cur, l);
		}
	}
	l.push_front(n);
}

list<node *> topological_sort(const vector<node *> &G)
{
	list<node *> sorted;
	for (size_t i = 0; i < G.size(); i++)
		if (!G[i]->visited)
			dfs_visit(G[i], sorted);
	return sorted;
}

void relax(node *n, edge *e)
{
	if (e->to->d > (n->d + e->w)) {
		e->to->d = n->d + e->w;
		e->to->p = n;
	}
}

void dag_shortest_path(const vector<node *> &G, node *s)
{
	s->d = 0;

	list<node *> sorted = topological_sort(G);

	cout << "sorted: ";
	for (list<node *>::iterator it = sorted.begin(); it != sorted.end(); ++it) {
		node *n = *it;
		cout << n->v << " ";
	}
	cout << endl << endl;

	for (list<node *>::iterator it = sorted.begin(); it != sorted.end(); ++it) {
		node *n = *it;
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
	const int r = 0;
	const int s = 1;
	const int t = 2;
	const int x = 3;
	const int y = 4;
	const int z = 5;

	vector<node *> G(6);
	G[r] = new node('r');
	G[s] = new node('s');
	G[t] = new node('t');
	G[x] = new node('x');
	G[y] = new node('y');
	G[z] = new node('z');

	add_edge(G, r, s, 5);
	add_edge(G, r, t, 3);
	add_edge(G, s, t, 2);
	add_edge(G, s, x, 6);
	add_edge(G, t, x, 7);
	add_edge(G, t, y, 4);
	add_edge(G, t, z, 2);
	add_edge(G, x, y, -1);
	add_edge(G, x, z, 1);
	add_edge(G, y, z, -2);

	dag_shortest_path(G, G[s]);

	for (size_t i = 0; i < G.size(); i++) {
		cout << G[i]->v << " (" << G[i]->d << ") parent: ";
		if (G[i]->p)
			cout << G[i]->p->v << endl;
		else
			cout << "NULL" << endl;
	}

	for (size_t i = 0; i < G.size(); i++) {
		node *n = G[i];
		for (size_t j = 0; j < n->adj.size(); j++)
			delete n->adj[j];
		delete n;
	}

	return 0;
}
