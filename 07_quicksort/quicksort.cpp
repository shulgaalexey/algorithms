#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void swap(int *a, int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

int partition(int *a, int p, int r) {
	int pivot = a[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (a[j] <= pivot) {
			i++;
			swap(a, i, j);
		}
	}
	swap(a, i + 1, r);
	return i + 1;
}

void quicksort(int *a, int p, int r) {
	if (p < r) {
		int q = partition(a, p, r);
		quicksort(a, p, q - 1);
		quicksort(a, q + 1, r);
	}
}

int partition_randomized(int *a, int p, int r) {
	int pivot_index = p + rand() % (r - p + 1);
	swap(a, r, pivot_index);
	return partition(a, p, r);
}

void quicksort_randomized(int *a, int p, int r) {
	if (p < r) {
		int q = partition_randomized(a, p, r);
		quicksort_randomized(a, p, q - 1);
		quicksort_randomized(a, q + 1, r);
	}
}

int main(void) {
	srand(time(NULL));

	{ // 0
		int a[] = {2, 8, 7, 1, 3, 5, 6, 4};
		const int n = int(sizeof(a) / sizeof(a[0]));
		quicksort(a, 0, n - 1);
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl << endl;
	}

	for (int test = 1; test < 20; test++) {
		const int n = test;
		int a[n] = {0};
		for (int i = 0; i < n; i++) {
			a[i] = rand() % 10;
			cout << a[i] << " ";
		}
		cout << endl;
		quicksort(a, 0, n - 1);
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;

		for (int i = 1; i < n; i++) {
			if (a[i] < a[i - 1]) {
				cout << "ERROR" << endl;
				return 1;
			}
		}
		cout << "OK" << endl << endl;
	}

	for (int test = 1; test < 40; test++) {
		const int n = test;
		int a[n] = {0};
		for (int i = 0; i < n; i++) {
			a[i] = rand() % 20;
			cout << a[i] << " ";
		}
		cout << endl;
		quicksort_randomized(a, 0, n - 1);
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;

		for (int i = 1; i < n; i++) {
			if (a[i] < a[i - 1]) {
				cout << "ERROR" << endl;
				return 1;
			}
		}
		cout << "OK" << endl << endl;
	}


	return 0;
}
