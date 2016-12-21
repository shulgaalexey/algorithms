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
		if ((left.v > right.v) && (left.v > crossed.v))
			return left;
		else if ((right.v > left.v) && (right.v > crossed.v))
			return right;
		else
			return crossed;
	}
}

int main(void) {
	{
		int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
		const int n = int(sizeof(a) / sizeof(a[0]));
		max_item_s r = find_max_subarray(a, 0, n - 1);
		cout << r.v << " at [" << r.from << ", " << r.to << "]" << endl;
	}

	{
		int a[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4};
		const int n = int(sizeof(a) / sizeof(a[0]));
		max_item_s r = find_max_subarray(a, 0, n - 1);
		cout << r.v << " at [" << r.from << ", " << r.to << "]" << endl;
	}
	return 0;
}
