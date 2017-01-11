#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

struct list {
	double v;
	list *next;
	list(const double &val) : v(val), next(NULL) {}
};

list *insertion_sort(list *l)
{
	list *res = NULL; // sorted result
	while (l) {
		// Extract next item from the input
		list *item = l;
		l = l->next;
		item->next = NULL;

		// Insert item into sorted result
		list *h = res;
		list *prev_h = NULL;
		while (h && (h->v <= item->v)) {
			prev_h = h;
			h = h->next;
		}

		if (prev_h) {
			prev_h->next = item;
			item->next = h;
		} else {
			item->next = res;
			res = item;
		}
	}
	return res;
}

void bucket_sort(double *a, const int n) {
	list *c[10] = {0};

	// Putting input items into 10 buckets
	for (int i = 0; i < n; i++) {
		list *item = new list(a[i]);
		const int bucket_no = a[i] * 10.;
		if (c[bucket_no])
			item->next = c[bucket_no];
		c[bucket_no] = item;
	}

	// Sorting buckets
	for (int i = 0; i < 10; i++) {
		if (c[i])
			c[i] = insertion_sort(c[i]);
	}

	// Concatenating sorted buckets into output array
	int idx = 0;
	for (int i = 0; i < 10; i++) {
		list *l = c[i];
		while (l) {
			a[idx] = l->v;
			idx++;
			l = l->next;
		}
	}

	// Releasing buckets
	for (int i = 0; i < 10; i++) {
		list *l = c[i];
		while (l) {
			list *item = l;
			l = l->next;
			delete item;
		}
	}
}

int main(void) {
	{ // 0
		double a[] = {.79, .13, .16, .64, .39, .20, .89, .53, .71, .42};
		const int n = int(sizeof(a) / sizeof(a[0]));
		bucket_sort(a, n);
		for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;
	}

	// random load tests
	srand(time(NULL));

	for (int test = 0; test < 10; test++) {
		cout << "test: " << test;
		const int n = 15 + test;
		double a[n] = {0};
		for (int i = 0; i < n; i++)
			a[i] = double(rand() % 100) / 100.;

		bucket_sort(a, n);

		/*for (int i = 0; i < n; i++)
			cout << a[i] << " ";
		cout << endl;*/

		for (int i = 1; i < n; i++) {
			if (a[i] < a[i - 1]) {
				cout << " ERROR" << endl;
				return 1;
			}
		}

		cout << " OK" << endl;
	}


	return 0;
}
