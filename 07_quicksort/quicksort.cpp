#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void swap(int *a, int i, int j) {
	int tmp = a[i];
	a[i] = a[j];
	a[j] = tmp;
}

// Regular partition ----------------------------------------------------------
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

// Randomized partition --------------------------------------------------------
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

// Hoare partition -------------------------------------------------------------
int partition_hoare(int *a, int p, int r) {
	int x = a[p];
	int i = p - 1;
	int j = r + 1;
	while (true) {

		do {
			j--;
		} while (a[j] > x);

		do {
			i++;
		} while (a[i] < x);

		if (i < j)
			swap(a, i, j);
		else
			return j;
	}
}

void quicksort_hoare(int *a, int p, int r) {
	if (p < r) {
		int q = partition_hoare(a, p, r);
		quicksort_hoare(a, p, q);
		quicksort_hoare(a, q + 1, r);
	}
}

// Tests -----------------------------------------------------------------------
bool check_sorted(int *a, int n, int *x, const string &tag) {
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) {
			cout << "ERROR: " << tag << endl;

			for (int i = 0; i < n; i++)
				cout << x[i] << " ";
			cout << endl;

			for (int i = 0; i < n; i++)
				cout << a[i] << " ";
			cout << endl;

			return false;
		}
	}
	return true;
}

int main(void) {
	srand(time(NULL));

	{ // 0 (regular partition)
		int a[] = {2, 8, 7, 1, 3, 5, 6, 4};
		const int n = int(sizeof(a) / sizeof(a[0]));
		quicksort(a, 0, n - 1);
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl << endl;
	}

	{ // 1 (Hoare partition)
		int a[] = {2, 8, 7, 1, 3, 5, 6, 4};
		const int n = int(sizeof(a) / sizeof(a[0]));
		quicksort_hoare(a, 0, n - 1);
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl << endl;
		//return 0;
	}

	// Regular, Randomized and Hoare partition
	for (int test = 1; test < 40; test++) {
		const int n = test;
		int a[n] = {0};
		int b[n] = {0};
		int c[n] = {0};
		int x[n] = {0};

		if (test == 13) { // Same value
			cout << "--> same values..." << endl;
			for (int i = 0; i < n; i ++) {
				a[i] = 13;
				b[i] = 13;
				c[i] = 13;
				x[i] = 13;
			}
		} else if (test == 14) { // Increasing
			cout << "--> increasing..." << endl;
			for (int i = 0; i < n; i ++) {
				a[i] = i;
				b[i] = i;
				c[i] = i;
				x[i] = i;
			}
		} else if (test == 15) { // Decreasing
			cout << "--> decreasing..." << endl;
			for (int i = 0; i < n; i ++) {
				a[i] = 20 - i;
				b[i] = 20 - i;
				c[i] = 20 - i;
				x[i] = 20 - i;
			}
		} else { // Random values
			for (int i = 0; i < n; i++) {
				a[i] = rand() % 20;
				b[i] = a[i];
				c[i] = a[i];
				x[i] = a[i];
			}
		}

		// Regular partition
		quicksort(a, 0, n - 1);
		if (!check_sorted(a, n, x, "regular"))
			return 1;

		// Regular partition
		quicksort_randomized(b, 0, n - 1);
		if (!check_sorted(b, n, x, "randomized"))
			return 2;

		// Hoare partition
		quicksort_hoare(c, 0, n - 1);
		if (!check_sorted(c, n, x, "hoare"))
			return 3;

		cout << "test: " << test << " OK" << endl;
	}

	return 0;
}
