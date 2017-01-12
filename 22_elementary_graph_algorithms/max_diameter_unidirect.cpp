#include <iostream>
#include <queue>
using namespace std;

struct list {
	int v;
	list *next;
	list(int a) : v(a), next(NULL) {}
};

int calc_diameter(list **G, const int n)
{
	int *D = new int[n]; // Distances

	for (int j = 0; j < n; j++)
		D[j] = -1;

	queue<int> q;
	q.push(0);
	D[0] = 0;
	int last = 0;
	while (!q.empty()) {
		const int node = q.front();
		q.pop();
		last = node;
		list *l = G[node];
		while (l) {
			if (D[l->v] < 0) {
				D[l->v] = D[node] + 1;
				q.push(l->v);
			}
			l = l->next;
		}
	}

	int max_d = 0;
	for (int j = 0; j < n; j++)
		D[j] = -1;

	q.push(last);
	D[last] = 0;
	while (!q.empty()) {
		const int node = q.front();
		q.pop();
		if (D[node] > max_d)
			max_d = D[node];
		list *l = G[node];
		while (l) {
			if (D[l->v] < 0) {
				D[l->v] = D[node] + 1;
				q.push(l->v);
			}
			l = l->next;
		}
	}

	delete [] D;
	return max_d;
}




int main(void) {
	const int n = 5;
	list **G = new list*[n];

	// D = 3
	G[0] = new list(1);
	G[0]->next = new list(2);
	G[1] = new list(0);
	G[1]->next = new list(2);
	G[1]->next->next = new list(4);
	G[2] = new list(0);
	G[2]->next = new list(1);
	G[2]->next->next = new list(3);
	G[3] = new list(4);
	G[4] = new list(1);
	G[4]->next = new list(2);
	G[4]->next->next = new list(3);


	// D = 2
	/*G[0] = new list(1);
	G[0]->next = new list(2);
	G[0]->next->next = new list(3);
	G[0]->next->next->next = new list(4);
	G[1] = new list(0);
	G[2] = new list(0);
	G[3] = new list(0);
	G[4] = new list(0);*/

	cout << calc_diameter(G, n) << endl;

	for (int i = 0; i < n; i ++) {
		list *l = G[i];
		while (l) {
			list *tmp = l;
			l = l->next;
			delete tmp;
		}
	}
	delete [] G;
	return 0;
}
