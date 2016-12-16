#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void merge(int *a, const int p, const int q, const int r) {

	// Extracting left sorted sub-array
	const int n1 = q - p + 1;
	int left[n1 + 1] = {0};
	for (int idx = 0, i = p; i <= q; i ++, idx ++)
		left[idx] = a[i];
	left[n1] = 1000000;

	// Extracting right sorted sub-array
	const int n2 = r - q;
	int right[n2 + 1] = {0};
	for (int idx = 0, i = (q + 1); i <= r; i ++, idx ++)
		right[idx] = a[i];
	right[n2] = 1000000;

	// Merging left and right sub-arrays into resulting sorted array
	for (int i = 0, j = 0, k = p; k <= r; k ++) {
		if (left[i] < right[j])
			a[k] = left[i ++];
		else
			a[k] = right[j ++];
	}
}

void merge_sort(int *a, const int p, const int r) {
	if (p < r) {
		const int q = (p + r) / 2;
		merge_sort(a, p, q);
		merge_sort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

int main(void) {
	srand(time(NULL));

	const int n = 7;
	int a[n] = {0};
	for (int i = 0; i < n; i ++) {
		a[i] = rand() % 10;
		cout << a[i] << " ";
	}
	cout << endl;

	merge_sort(a, 0, n - 1);

	for (int i = 0; i < n; i ++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
