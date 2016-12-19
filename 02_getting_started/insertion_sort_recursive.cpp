#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void insert(const int v, int *a, const int n) {
	int idx = n - 2;
	while ((idx >= 0) && (a[idx] > v)) {
		a[idx + 1] = a[idx];
		idx --;
	}
	a[idx + 1] = v;
}

void insertion_sort_recursive(int *a, const int n) {
	if (n == 1)
		return;
	insertion_sort_recursive(a, n - 1);
	insert(a[n - 1], a, n);
}

int main(void) {

	{ // 1
		int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
		const int n = int(sizeof(a) / sizeof(a[0]));

		for (int i = 0; i < n; i ++)
			cout << a[i] << " ";
		cout << endl;

		insertion_sort_recursive(a, n);

		for (int i = 0; i < n; i ++)
			cout << a[i] << " ";
		cout << endl << endl;
	}

	{ // 2
		int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		const int n = int(sizeof(a) / sizeof(a[0]));

		for (int i = 0; i < n; i ++)
			cout << a[i] << " ";
		cout << endl;

		insertion_sort_recursive(a, n);

		for (int i = 0; i < n; i ++)
			cout << a[i] << " ";
		cout << endl << endl;
	}

	srand(time(NULL));

	for (int test = 0; test < 5; test ++) {
		const int n = 8;
		int a[n] = {0};
		for (int i = 0; i < n; i ++) {
			a[i] = rand() % 10;
			cout << a[i] << " ";
		}
		cout << endl;

		insertion_sort_recursive(a, n);

		for (int i = 0; i < n; i ++)
			cout << a[i] << " ";
		cout << endl;

		for (int i = 1; i < n; i ++) {
			if (a[i] < a[i - 1])
				cout << "ERROR" << endl;
		}

		cout << endl;
	}

	return 0;
}
