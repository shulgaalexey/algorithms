#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct node {
	char v;
	bool visited;
	vector<node *> adj;
	node(char a) : v(a), visited(false) {}
};

int count_pathes(node *s, node *f)
{
	if (s == f)
		return 1;
	int cnt = 0;
	for (size_t i = 0; i < s->adj.size(); i++) {
		node *n = s->adj[i];
		if (!n->visited) {
			n->visited = true;
			cnt += count_pathes(n, f);
			n->visited = false;
		}
	}
	return cnt;
}

void link(map<char, node *> &G, char src, char dst)
{
	G[src]->adj.push_back(G[dst]);
}

int main(void)
{
	map<char, node *> G;
	for (char ch = 'm'; ch <= 'z'; ch++)
		G[ch] = new node(ch);

	link(G, 'm', 'r');
	link(G, 'm', 'q');
	link(G, 'm', 'x');

	link(G, 'n', 'o');
	link(G, 'n', 'u');
	link(G, 'n', 'q');

	link(G, 'o', 'r');
	link(G, 'o', 's');
	link(G, 'o', 'v');

	link(G, 'p', 'o');
	link(G, 'p', 's');
	link(G, 'p', 'z');

	link(G, 'q', 't');

	link(G, 'r', 'u');
	link(G, 'r', 'y');

	link(G, 's', 'r');

	//link(G, 't', '');

	link(G, 'u', 't');

	link(G, 'v', 'x');
	link(G, 'v', 'w');

	link(G, 'w', 'z');

	//link(G, 'x', '');

	link(G, 'y', 'v');

	//link(G, 'z', '');

	const int cnt = count_pathes(G['p'], G['v']);
	cout << cnt << endl;

	for (char ch = 'm'; ch < 'z'; ch++)
		delete G[ch];
	return 0;
}
