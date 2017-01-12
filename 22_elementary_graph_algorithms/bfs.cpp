#include <iostream>
#include <queue>
using namespace std;

struct list {
	int v;
	list *next;
	list(int a) : v(a), next(NULL) {}
};

list **G = NULL;
int n = 0;
int *D = NULL; // Distances
int *P = NULL; // Parents
bool *V = NULL; // Visited
int start = 0;

void reset(const int N)
{
	if (G) {
		for (int i = 0; i < n; i++) {
			list *l = G[i];
			while (l) {
				list *tmp = l;
				l = l->next;
				delete tmp;
			}
		}
		delete [] G;
	}

	if (D)
		delete [] D;
	if (P)
		delete [] P;
	if (V)
		delete [] V;

	G = NULL;
	D = NULL;
	P = NULL;
	V = NULL;

	n = N;
	if (n > 0) {
		G = new list*[n];
		D = new int[n];
		P = new int[n];
		V = new bool[n];
		for (int i = 0; i < n; i++) {
			G[i] = NULL;
			D[i] = -1;
			P[i] = -1;
			V[i] = false;
		}
	}
}

void bfs()
{
	queue<int> q;
	q.push(start);
	D[start] = 0;
	V[start] = true;
	while (!q.empty()) {
		const int node = q.front();
		q.pop();
		list *l = G[node];
		while (l) {
			if (!V[l->v]) {
				q.push(l->v);
				D[l->v] = D[node] + 1;
				P[l->v] = node;
				V[l->v] = true;
			}
			l = l->next;
		}
	}
}

void trace_distances()
{
	cout << "Distances:" << endl;
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		if (i == start)
			cout << "START ";
		else if (D[i] > 0)
			cout << D[i] << " ";
		else
			cout << "INF ";
		cout << endl;
	}
	cout << endl;
}

void trace_path(const int node)
{
	if (node == start) {
		cout << start << endl;
	} else if (node == (-1)) {
		cout << "NO WAY" << endl;
	}	else {
		cout << node << " ";
		trace_path(P[node]);
	}
}

int main(void)
{
	for (int test = 0; test < 6; test ++) {
		cout << "==================" << endl;
		cout << "Test: " << test << endl;

		start = test;

		reset(6);

		G[0] = new list(1);
		G[0]->next = new list(3);
		G[1] = new list(4);
		G[2] = new list(4);
		G[2]->next = new list(5);
		G[3] = new list(1);
		G[4] = new list(3);
		G[5] = new list(5);

		//start = 2;
		bfs();

		trace_distances();

		for (int i = 0; i < n; i ++) {
			cout << "Path to " << i << ": ";
			trace_path(i);
		}

		reset(0);
	}

	return 0;
}
