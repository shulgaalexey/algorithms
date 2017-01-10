#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int digit(int v, const int d)
{
	for (int i = 0; i < d; i++)
		v /= 10;
	return v % 10;
}

void counting_sort_radix(int *a, int *b, const int n, const int d, const int k)
{
	int *c = new int[k + 1];
	for (int i = 0; i <= k; i++)
		c[i] = 0;

	for (int i = 0; i < n; i++)
		c[digit(a[i], d)]++;

	for (int i = 1; i <= k; i++)
		c[i] += c[i - 1];

	for (int i = (n -1); i >= 0; i--) {
		b[c[digit(a[i], d)] - 1] = a[i];
		c[digit(a[i], d)]--;
	}

	delete [] c;
}

void radix_sort(int *a, int *b, const int n, const int d)
{
	for (int i = 0; i < d; i++) {
		counting_sort_radix(a, b, n, i, 9);
		int *tmp = b;
		b = a;
		a = tmp;
	}
	b = a;
}




int main(void)
{
	{ // counting sort test
		int a[] = {2, 5, 3, 0, 2, 3, 0, 3};
		const int n = int(sizeof(a) / sizeof(a[0]));
		int b[n] = {0};
		counting_sort_radix(a, b, n, 0, 5);
		for (int i = 0; i < n; i++)
			cout << b[i] << " ";
		cout << endl;
	}

	{ // radix sort
		int a[] = {
			329,
			457,
			657,
			839,
			436,
			720,
			355};
		const int n = int(sizeof(a) / sizeof(a[0]));
		int b[n] = {0};
		radix_sort(a, b, n, 3);
		for (int i = 0; i < n; i++)
			cout << b[i] << endl;
	}

	{ // random input
		srand(time(NULL));
		cout << "=======================" << endl;
		for (int test = 0; test < 10; test ++) {
			cout << "test: " << test << endl;

			const int n = 25 + test % 2;
			int a[n] = {0};
			int b[n] = {0};
			int c[n] = {0};
			for (int i = 0; i < n; i++) {
				a[i] = rand() % 1000;
				c[i] = a[i];
			}

			radix_sort(a, b, n, 3);

			for (int i = 1; i < n; i++) {
				if (b[i] >= b[i - 1])
					continue;
				// ERROR
				cout << "ERROR in array:" << endl;
				for (int j = 0; j < n; j++)
					cout << c[j];
				cout << endl;
				return 1;
			}
			cout << "OK" << endl;
		}
	}
	return 0;
}
