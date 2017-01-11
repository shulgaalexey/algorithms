#include <iostream>
using namespace std;

void transpose_matrix(int *u, int *v, const int e_cnt, const int v_cnt)
{
	int *G = new int[v_cnt * v_cnt];
	for (int i = 0; i < (v_cnt * v_cnt); i++)
		G[i] = 0;

	// Initializing adjacent matrix
	for (int e = 0; e < e_cnt; e++)
		G[u[e] * v_cnt + v[e]] = 1;

	// Priniting original graph's adjacent matrix
	for (int i = 0; i < v_cnt; i++) {
		for (int j = 0; j < v_cnt; j++)
			cout << G[i * v_cnt + j] << " ";
		cout << endl;
	}
	cout << endl;

	// Transposing
	for (int i = 0; i < v_cnt; i++) {
		for (int j = 0; j < (i + 1); j++) {
			int tmp = G[i * v_cnt + j];
			G[i * v_cnt + j] = G[j * v_cnt + i];
			G[j * v_cnt + i] = tmp;
		}
	}

	// Priniting transposed graph's adjacent matrix
	for (int i = 0; i < v_cnt; i++) {
		for (int j = 0; j < v_cnt; j++)
			cout << G[i * v_cnt + j] << " ";
		cout << endl;
	}
	cout << endl;

	delete [] G;
}

struct list {
	int v;
	list *next;
	list(int a) : v(a), next(NULL) {}
};

void transpose_list(int *u, int *v, const int e_cnt, const int v_cnt)
{
	list **Adj = new list*[v_cnt];
	for (int i = 0; i < v_cnt; i++)
		Adj[i] = NULL;

	// Initializing adjacent lists
	for (int e = 0; e < e_cnt; e++) {
		list *edge = new list(v[e]);
		edge->next = Adj[u[e]];
		Adj[u[e]] = edge;
	}

	// Priniting original graph's adjacent lists
	for (int i = 0; i < v_cnt; i++) {
		cout << i << ": ";
		list *l = Adj[i];
		while (l) {
			cout << l->v << " ";
			l = l->next;
		}
		cout << endl;
	}
	cout << endl;

	list **AdjT = new list*[v_cnt];
	for (int i = 0; i < v_cnt; i++)
		AdjT[i] = NULL;

	// Transposing
	for (int i = 0; i < v_cnt; i++) {
		list *l = Adj[i];
		while (l) {
			list *edge = new list(i);
			edge->next = AdjT[l->v];
			AdjT[l->v] = edge;
			l = l->next;
		}
	}

	// Priniting transposed graph's adjacent lists
	for (int i = 0; i < v_cnt; i++) {
		cout << i << ": ";
		list *l = AdjT[i];
		while (l) {
			cout << l->v << " ";
			l = l->next;
		}
		cout << endl;
	}
	cout << endl;

	// Releasing memory
	for (int i = 0; i < v_cnt; i ++) {
		list *l = Adj[i];
		while (l) {
			list *item = l;
			l = l->next;
			delete item;
		}
		l = AdjT[i];
		while (l) {
			list *item = l;
			l = l->next;
			delete item;
		}
	}

	delete [] Adj;
	delete [] AdjT;
}

int main(void) {
	{ // Matrix-based transposing
		int u[] = {0, 0, 0, 1, 1, 3, 3, 4};
		int v[] = {1, 3, 4, 3, 4, 0, 4, 0};
		const int e_cnt = int(sizeof(u) / sizeof(u[0]));
		const int v_cnt = 5;
		transpose_matrix(u, v, e_cnt, v_cnt);
	}
	{ // List-based transposing
		int u[] = {0, 0, 0, 1, 1, 3, 3, 4};
		int v[] = {1, 3, 4, 3, 4, 0, 4, 0};
		const int e_cnt = int(sizeof(u) / sizeof(u[0]));
		const int v_cnt = 5;
		transpose_list(u, v, e_cnt, v_cnt);
	}
	return 0;
}
