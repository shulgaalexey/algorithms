#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct max_item_s {
	int v;
	int from;
	int to;
};

max_item_s find_max_crossed_subarray(int *a,
		const int from, const int mid, const int to) {
	int sum_left = 0;
	int left_idx = mid;
	int left_max = -1000;
	for (int i = mid; i >= from; i --) {
		sum_left += a[i];
		if (sum_left > left_max) {
			left_max = sum_left;
			left_idx = i;
		}
	}

	int sum_right = 0;
	int right_idx = mid + 1;
	int right_max = -1000;
	for (int i = (mid + 1); i <= to; i ++) {
		sum_right += a[i];
		if (sum_right > right_max) {
			right_max = sum_right;
			right_idx = i;
		}
	}

	const max_item_s ret = {left_max + right_max, left_idx, right_idx};
	return ret;
}

max_item_s find_max_subarray(int *a, const int from, const int to) {
	if (from >= to) {
		const max_item_s single = {a[to], to, to};
		return single;
	} else {
		const int mid = (to + from) / 2;
		max_item_s left = find_max_subarray(a, from, mid);
		max_item_s right = find_max_subarray(a, mid + 1, to);
		max_item_s crossed = find_max_crossed_subarray(a, from, mid, to);

		max_item_s candidate = {0};
		if ((left.v > right.v) && (left.v > crossed.v))
			candidate = left;
		else if ((right.v > left.v) && (right.v > crossed.v))
			candidate = right;
		else
			candidate = crossed;

		// One of dirty hacks.
		// Actually there is one more bug here.
		for (int i = from; i <= to; i++) {
			if (a[i] > candidate.v) {
				candidate.v = a[i];
				candidate.from = i;
				candidate.to = i;
			}
		}

		return candidate;
	}
}

max_item_s find_max_subarray_linear(int *a, const int from, const int to) {
	int global_max = -1000000;
	int cur_sum = 0;

	for (int i = from; i <= to; i++) {
		cur_sum += a[i];
		cur_sum = max(0, cur_sum);
		global_max = max(global_max, cur_sum);
	}

	const max_item_s ret = {global_max, -1, -1};
	return ret;
}

int main(void) {
	{ // 1
		int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
		const int n = int(sizeof(a) / sizeof(a[0]));
		const max_item_s r = find_max_subarray(a, 0, n - 1);
		cout << r.v << " at [" << r.from << ", " << r.to << "]" << endl;
	}

	{ // 2
		int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4};
		const int n = int(sizeof(a) / sizeof(a[0]));
		const max_item_s r = find_max_subarray(a, 0, n - 1);
		cout << r.v << " at [" << r.from << ", " << r.to << "]" << endl;
	}

	{ // 3 (linear)
		int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
		const int n = int(sizeof(a) / sizeof(a[0]));
		max_item_s r = find_max_subarray_linear(a, 0, n - 1);
		cout << r.v << " at [" << r.from << ", " << r.to << "]" << endl;
	}

	{ // load tests
		srand(time(NULL));
		for (int test = 5; test <= 100; test++) {
			if ((test % 5) == 0)
				cout << "test" << test << endl;
			const int n = test;
			int a[n] = {0};
			for (int i = 0; i < n; i++)
				a[i] = -10 + rand() % 20;

			const max_item_s r1 = find_max_subarray(a, 0, n - 1);
			const max_item_s r2 = find_max_subarray_linear(a, 0, n - 1);

			if (r1.v != r2.v) {
				cout << "ERROR: " << r1.v << " != " << r2.v << endl;
				for (int i = 0; i < n; i ++)
					cout << a[i] << ", ";
				cout << endl;
				return 1;
			}
		}
		cout << "OK" << endl;

	}
	return 0;
}
