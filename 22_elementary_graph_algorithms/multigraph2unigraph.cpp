#include <iostream>
using namespace std;

struct list {
	int v;
	list *next;
	list(int a) : v(a), next(NULL) {}
};

bool find(list *l, int v) {
	while (l) {
		if (l->v == v)
			return true;
		l = l->next;
	}
	return false;
}

list *add(list *l, int v) {
	if (find(l, v))
		return l;
	list *item = new list(v);
	item->next = l;
	return item;
}

void multigraph2unigraph(list **G, const int n)
{
	list **GU = new list*[n];
	for (int i = 0; i < n; i++)
		GU[i] = NULL;

	for (int i = 0; i < n; i++) {
		list *l = G[i];
		while (l) {
			if (l->v == i) {
				l = l->next;
				continue;
			}
			if (find(G[l->v], i)) {
				GU[i] = add(GU[i], l->v);
				GU[l->v] = add(GU[l->v], i);
			}
			l = l->next;
		}
	}

	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		list *l = GU[i];
		while (l) {
			cout << l->v << " ";
			l = l->next;
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++) {
		list *l = GU[i];
		while (l) {
			list *tmp = l;
			l = l->next;
			delete tmp;
		}
	}
	delete [] GU;
}

int main(void) {
	list *G[5] = {0};
	G[0] = new list(1);
	G[0]->next = new list(4);
	G[1] = new list(0);
	G[1]->next = new list(2);
	G[1]->next->next = new list(4);
	G[2] = new list(3);
	G[3] = new list(3);
	G[3]->next = new list(4);
	G[3]->next->next = new list(2);
	G[4] = new list(3);

	multigraph2unigraph(G, 5);

	for (int i = 0; i < 5; i++) {
		list *l = G[i];
		while (l) {
			list *tmp = l;
			l = l->next;
			delete tmp;
		}
	}

	return 0;
}
