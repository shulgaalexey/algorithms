#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void selection_sort(int *a, const int n) {
	for (int i = 0; i < (n - 1); i ++) {
		int min_index = i;
		for (int j = i + 1; j < n; j ++) {
			if (a[j] < a[min_index])
				min_index = j;
		}
		int tmp = a[i];
		a[i] = a[min_index];
		a[min_index] = tmp;
	}
}

int main(void) {
	srand(time(NULL));

	const int n = 7;
	int *a = new int[n];
	for (int i = 0; i < n; i ++) {
		a[i] = rand() % 10;
		cout << a[i] << " ";
	}
	cout << endl;

	selection_sort(a, n);

	for (int i = 0; i < n; i ++)
		cout << a[i] << " ";
	cout << endl;

	return 0;
}
