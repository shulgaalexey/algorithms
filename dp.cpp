// Dynamic Programming algs
// Examples considered:
// 1. Rod cutting problem
//   - bottom up approach
//   - memoization
// 2. Fibonacci calculation with O(N)
//

#include <iostream>
using namespace std;

int inline max(int a, int b) {
	return (a > b) ? a : b;
}

int dp_bottom_up(int *p, int n) { // p[0] = 0
	int *r = new int[n + 1];
	r[0] = 0;

	for(int i = 1; i <= n; i ++) {
		r[i] = 0;
		for(int j = 1; j <= i; j ++)
			r[i] = max(p[j] + r[i - j], r[i]);
	}

	const int ret = r[n];
	delete [] r;
	return ret;
}

int dp_memoized_aux(int *p, int n, int *memo, int *history) {
	if(memo[n] > 0)
		return memo[n];
	if((n == 0) || (n == 1))
		return p[n]; // 0 or 1

	int q = -1;
	for(int i = 1; i <= n; i ++) {
		int tmp = p[i] + dp_memoized_aux(p, n - i, memo, history);
		if(tmp > q) {
			q = tmp;
			if(history)
				history[n] = i;
		}
		//q = max(q, p[i] + dp_memoized_aux(p, n - i, memo));
	}
	memo[n] = q;
	return q;
}

int dp_memoized(int *p, int n, int *history) {
	int *memo = new int[n + 1];
	for(int i = 0; i <= n; i ++)
		memo[i] = -1;

	const int ret = dp_memoized_aux(p, n, memo, history);
	delete [] memo;
	return ret;
}

int fibonacci(int n) {
	if(n <= 1)
		return 1;
	int *r = new int[n + 1];
	r[0] = 1;
	r[1] = 1;

	for(int i = 2; i <= n; i ++)
		r[i] = r[i - 1] + r[i - 2];
	const int ret = r[n];
	delete [] r;
	return ret;
}



int main(void) {
	int p[] = {0, 1, 5, 8, 10, 13, 17, 17, 20, 24, 30};
	const int n = int(sizeof(p) / sizeof(p[0]));

	int check[] = {0, 1, 5, 8, 10, 13, 17, 18, 22, 25, 30};
	for(int i = 0; i < (n - 1); i ++) {
		const int ret1 = dp_bottom_up(p, i);
		if(ret1 != check[i])
			cout << "Error Bottom Up: Expected " << check[i] << " obtained " << ret1 << endl;
		const int ret2 = dp_memoized(p, i, NULL);
		if(ret2 != check[i])
			cout << "Error Memoized: Expected " << check[i] << " obtained " << ret2 << endl;
	}

	{ // return the actual solution
		const int l = 9;
		int *history = new int[l + 1];
		dp_memoized(p, l, history);
		int rod_remainder = l;
		while(rod_remainder) {
			cout << "cut " << history[rod_remainder] << endl;
			rod_remainder -= history[rod_remainder];
		}

		delete [] history;
	}

	{ // Fibonacci
		cout << endl << "Fibonacci numbers:" << endl;
		for(int i = 0; i < 10; i ++)
			cout << i << ": " << fibonacci(i) << endl;
	}

	return 0;
}
