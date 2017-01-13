#include <iostream>
#include <vector>
using namespace std;

enum color_e {
	WHITE,
	GRAY,
	BLACK
};

struct node {
	char v;
	vector<node *> adj;
	node *p;
	color_e c;
	int d;
	int f;
	node(char ch) : v(ch), p(NULL), c(WHITE), d(0), f(0) {}
};

int __time = 0;

void dfs_visit(node *n)
{
	__time++;
	n->d = __time;
	n->c = GRAY;
	for (size_t i = 0; i < n->adj.size(); i++) {
		node *cur = n->adj[i];
		if (cur->c == WHITE) {
			cur->p = n;
			dfs_visit(cur);
		}
	}
	__time++;
	n->f = __time;
	n->c = BLACK;
}

void dfs(const vector<node *> &G)
{
	__time = 0;
	for (size_t i = 0; i < G.size(); i++)
		if (G[i]->c == WHITE)
			dfs_visit(G[i]);
}

void trace(const vector<node *> &G)
{
	for (size_t i = 0; i < G.size(); i++) {
		node *n = G[i];
		cout << n->v << " (" << n->d << "/" << n->f << ") ";
		switch (n->c) {
		case WHITE:
			cout << "WHITE ";
			break;
		case GRAY:
			cout << "GRAY ";
			break;
		case BLACK:
			cout << "BLACK ";
			break;
		}
		if (n->p)
			cout << "parent: " << n->p->v;
		else
			cout << "ROOT ";
		cout << " children: ";
		for (size_t j = 0; j < n->adj.size(); j++)
			cout << n->adj[j]->v << " ";
		cout << endl;
	}
	cout << endl;
}

int main(void)
{
	vector<node *> G(6);
	G[0] = new node('u');
	G[1] = new node('v');
	G[2] = new node('w');
	G[3] = new node('x');
	G[4] = new node('y');
	G[5] = new node('z');

	G[0]->adj.push_back(G[1]);
	G[0]->adj.push_back(G[3]);
	G[1]->adj.push_back(G[4]);
	G[2]->adj.push_back(G[4]);
	G[2]->adj.push_back(G[5]);
	G[3]->adj.push_back(G[1]);
	G[4]->adj.push_back(G[3]);
	G[5]->adj.push_back(G[5]);

	trace(G);

	dfs(G);

	trace(G);

	for (size_t i = 0; i < G.size(); i++)
		delete G[i];
	return 0;
}
