#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void merge(int *a, const int p, const int q, const int r) {

	// Extracting left sorted sub-array
	const int n1 = q - p + 1;
	int left[n1] = {0};
	for (int idx = 0, i = p; i <= q; i ++, idx ++)
		left[idx] = a[i];

	// Extracting right sorted sub-array
	const int n2 = r - q;
	int right[n2] = {0};
	for (int idx = 0, i = (q + 1); i <= r; i ++, idx ++)
		right[idx] = a[i];

	// Merging left and right sub-arrays into resulting sorted array
	int i = 0;
	int j = 0;
	int k = p;
	for (; ((k <= r) && (i < n1) && (j < n2)); k ++) {
		if (left[i] < right[j])
			a[k] = left[i ++];
		else
			a[k] = right[j ++];
	}

	if (i < n1) {
		for (; i < n1; i ++, k ++)
			a[k] = left[i];
	} else {
		for (; j < n2; j ++, k ++)
			a[k] = right[j];
	}
}

void insertion_sort(int *a, const int n) {
	for (int j = 1; j < n; j ++) {
		int key = a[j];
		int i = j - 1;
		while ((i >= 0) && (a[i] > key)) {
			a[i + 1] = a[i];
			i --;
		}
		a[i + 1] = key;
	}
}

void merge_sort(int *a, const int p, const int r, const int k) {
	if ((r - p) <= k) {
		insertion_sort(a + p, r - p + 1);
	} else {
		const int q = (p + r) / 2;
		merge_sort(a, p, q, k);
		merge_sort(a, q + 1, r, k);
		merge(a, p, q, r);
	}
}

int main(void) {
	srand(time(NULL));

	for (int test = 0; test < 5; test ++) {

		const int n = 33;
		const int k = 5;
		int a[n] = {0};
		for (int i = 0; i < n; i ++) {
			a[i] = rand() % 10;
			cout << a[i] << " ";
		}
		cout << endl;

		merge_sort(a, 0, n - 1, k);

		for (int i = 0; i < n; i ++)
			cout << a[i] << " ";
		cout << endl;

		for (int i = 1; i < n; i ++) {
			if (a[i - 1] > a[i]) {
				cout << "ERROR!" << endl;
			}
		}

		cout << endl;
	}

	return 0;
}
