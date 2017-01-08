#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void counting_sort(int *a, int *b, const int n, const int k)
{
	int *c = new int[k + 1];
	for (int i = 0; i <= k; i++)
		c[i] = 0;

	// Now c[i] contains amount of each value in a.
	for (int i = 0; i < n; i++)
		c[a[i]]++;

	// Nw c[i] indicates how many items are before each a[i].
	for (int i = 1; i <= k; i++)
		c[i] += c[i - 1];

	// Populating b with items, indexed by c.
	for (int i = (n - 1); i >= 0; i--) {
		b[c[a[i]] - 1] = a[i];
		c[a[i]]--;
	}

	delete [] c;
}

int main(void)
{
	{ // 0
		int a[] = {2, 5, 3, 0, 2, 3, 0, 3};
		const int n = int(sizeof(a) / sizeof(a[0]));
		int b[n] = {0};
		const int k = 5;

		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;

		counting_sort(a, b, n, k);

		for (int i = 0; i < n; i++)
			cout << b[i] << " ";
		cout << endl << endl;
	}

	{ // rnd
		for (int test = 1; test < 10; test++) {
			const int n = 7 + rand() % 2;
			const int k = 5;
			int a[n] = {0};
			int b[n] = {0};

			for (int i = 0; i < n; i++) {
				a[i] = rand() % 6;
				cout << a[i] << " ";
			}
			cout << endl;

			counting_sort(a, b, n, k);

			for (int i = 0; i < n; i++)
				cout << b[i] << " ";
			cout << endl << endl;
		}
	}

	return 0;
}
