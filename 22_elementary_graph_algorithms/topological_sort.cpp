#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
using namespace std;

enum color_e {WHITE, GRAY, BLACK};

struct node {
	string v;
	node *p;
	vector<node *> adj;
	color_e c;
	int d;
	int f;
	node(const string &s) : v(s), p(NULL), c(WHITE), d(0), f(0) {}
};

int __time = 0;

void dfs_visit(node *n, list<node *> &sorted)
{
	__time++;
	n->d = __time;
	n->c = GRAY;
	for (size_t i = 0; i < n->adj.size(); i++) {
		if (n->adj[i]->c == WHITE) {
			n->adj[i]->p = n;
			dfs_visit(n->adj[i], sorted);
		}
	}
	__time++;
	n->f = __time;
	n->c = BLACK;
	sorted.push_front(n);
}

list<node *> topological_sort(const vector<node *> &G)
{
	list<node *> sorted;
	for (size_t i = 0; i < G.size(); i++)
		if (G[i]->c == WHITE)
			dfs_visit(G[i], sorted);
	return sorted;
}

const string UNDERSHORTS = "undershorts";
const string PANTS = "pants";
const string BELT = "belt";
const string SHIRT = "shirt";
const string TIE = "tie";
const string JACKET = "jacket";
const string SOCKS = "socks";
const string SHOES = "shoes";
const string WATCH = "watch";

int main(void) {
	map<string, node *> m;
	m[UNDERSHORTS] = new node(UNDERSHORTS);
	m[PANTS] = new node(PANTS);
	m[BELT] = new node(BELT);
	m[SHIRT] = new node(SHIRT);
	m[TIE] = new node(TIE);
	m[JACKET] = new node(JACKET);
	m[SOCKS] = new node(SOCKS);
	m[SHOES] = new node(SHOES);
	m[WATCH] = new node(WATCH);

	m[UNDERSHORTS]->adj.push_back(m[PANTS]);
	m[UNDERSHORTS]->adj.push_back(m[SHOES]);
	m[PANTS]->adj.push_back(m[SHOES]);
	m[BELT]->adj.push_back(m[JACKET]);
	m[SHIRT]->adj.push_back(m[TIE]);
	m[TIE]->adj.push_back(m[JACKET]);
	m[SOCKS]->adj.push_back(m[SHOES]);

	vector<node *> G;
	for (map<string, node *>::iterator it = m.begin(); it != m.end(); ++it)
		G.push_back(it->second);

	list<node *> l = topological_sort(G);

	cout << "Dressing order: " << endl;
	int order = 1;
	for (list<node *>::iterator it = l.begin(); it != l.end(); ++it) {
		node *n = (node *)*it;
		cout << order << ": " << n->v << "(" << n->d << "/" << n->f << ")" << endl;
		order++;
	}


	for (size_t i = 0; i < G.size(); i++)
		delete G[i];

	return 0;
}
