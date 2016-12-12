#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

void sort(int *a, const int n) {
	for(int j = 1; j < n; j ++) {
		int key = a[j];
		int i = j - 1;
		while((i >= 0) && (a[i] > key)) {
			a[i + 1] = a[i];
			i --;
		}
		a[i + 1] = key;
	}
}

int main(void) {

	srand(time(NULL));

	const int n = 15;
	int *a = new int[n];

	for(int i = 0; i < n ; i ++)
		a[i] = rand() % 10;

	for(int i = 0; i < n; i ++)
		cout << a[i] << " ";
	cout << endl;

	sort(a, n);

	for(int i = 0; i < n; i ++)
		cout << a[i] << " ";
	cout << endl;

	delete [] a;

	return 0;
}
