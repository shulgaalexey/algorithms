#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

#define LEFT(i) (i * 2 + 1);
#define RIGHT(i) (i * 2 + 2);
#define PARENT(i) (int((i - 1) / 2))

void swap(int *a, const int i, const int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

void max_heapify(int *a, const int n, const int i) {
	int largest = i;

	int l = LEFT(i);
	if ((l < n) && (a[l] > a[i]))
		largest = l;

	int r = RIGHT(i);
	if ((r < n) && (a[r] > a[largest]))
		largest = r;

	if (i != largest) {
		swap(a, i, largest);
		max_heapify(a, n, largest);
	}
}

void heap_sort(int *a, const int n) {
	for (int i = PARENT(n - 1); i >= 0; i--)
		max_heapify(a, n, i);

	for (int i = 0; i < (n - 1); i ++) {
		swap(a, 0, n - i - 1);
		max_heapify(a, n - i - 1, 0);
	}
}

int main(void) {
	{ // 0
		int a[] = {7, 6, 5, 4, 3, 2, 1};
		const int n = int(sizeof(a) / sizeof(a[0]));
		heap_sort(a, n);
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;
	}

	srand(time(NULL));

	{ // 1
		for (int test = 1; test < 10; test++) {
			cout << "test:" << test << endl;
			const int n = test;
			int a[n] = {0};
			for (int i = 0; i < n; i++) {
				a[i] = rand() % 10;
				cout << a[i] << " ";
			}
			cout << endl;

			heap_sort(a, n);

			for (int i = 0; i < n; i ++)
				cout << a[i] << " ";
			cout << endl;

			for (int i = 1; i < n; i++) {
				if (a[i] < a[i -1]) {
					cout << "ERROR" << endl;
					return 0;
				}
			}
			cout << "OK" << endl << endl;
		}
	}
	return 0;
}

