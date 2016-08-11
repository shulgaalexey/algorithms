// Dynamic Programming algs
// Examples considered:
// 1. Rod cutting problem
//   - bottom up approach
//   - memoization
// 2. Fibonacci calculation with O(N)
// 3. Matrix Chain Product problem
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

void print_parens(int *s, const int i, const int j, int length) {
	if(i == j)
		cout << "A" << i;
	else {
		cout << "(";
		print_parens(s, i, s[i * length + j], length);
		print_parens(s, s[i * length +  j] + 1, j, length);
		cout << ")";
	}
}

// Matrix Chain Product problem
int matrix_chain(int *p, const int length) { // length is a size of p, including p[0]
	const int n = length - 1;
	int m[length][length];
	int s[length][length];

	// Filling the main diagonal with zeros
	// because it indicates the product of matrix to itself
	// and its cost is zero
	for(int i = 1; i <= n; i ++) // l is 1: cost is 0
		m[i][i] = 0;

	// Filling other diagonals top to the main diagonal
	for(int l = 2; l <= n; l ++) { // l is a length of sequence of matrixes in the product
		for(int i = 1; i <= (n - l + 1); i ++ ) { // i is starting matrix in a sequence
			// we should try all matrices except the last on in the sequence

			const int j = i + l -1; // index of the last matrix in the sequence

			m[i][j] = 1000000; // pre-init, +inf

			for(int k = i; k <= (j - 1); k ++) { // trying all split points
				const int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if(q < m[i][j]) {
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	}

	// Reconstructing the solution
	print_parens((int *)s, 1, n, length);
	cout << endl;

	return m[1][n];
}

int main(void) {
	{ // Matrix chain problem
		int p[] = {30, 35, 15, 5, 10, 20, 25};
		const int ret = matrix_chain(p, int(sizeof(p) / sizeof(p[0])));
		if(ret != 15125)
			cout << "Error Matrix Chain: " << ret << endl;
		else
			cout << ret << " OK" << endl;
	}

	{ // Rod cutting problem
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
	}

	return 0;
}
