// Suppose that we are given a directed acyclic graph G = (V, E) with realvalued
// edge weights and two distinguished vertices s and t.
// Describe a dynamicprogramming
// approach for finding a longest weighted simple path from s to t.
// What does the subproblem graph look like? What is the efficiency of your algorithm?
#include <iostream>
using namespace std;

#define INF -100000.

double find_longest_path(const double *E, const int n) {
	double P[n][n] = {0}; // table with paths calculated

	for(int i = 0; i < n; i ++)
		P[i][i] = 0;

	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++) {
			if(i == j)
				continue;
			for(int r = 0; r < n; r ++) {
				if(r == j)
					P[i][j] = max(P[i][j], E[i * n + j]);
				else if(r != i) {
					const double tmp = P[i][r] + E[r * n + j];
					P[i][j] = max(P[i][j], tmp);
				}
			}
		}

		for(int j = 0; j < n; j ++)
			cout << P[i][j] << " ";
		cout << endl;
	}
	return P[0][n - 1];
}

int main(void) {
	const double E[5][5] = {
		0,   1,   3,   5,   7,
		INF, 0,   8,   INF, 2,
		INF, INF, 0,   9,   4,
		INF, INF, INF, 0,   6
		INF, INF, INF, INF, 0
	};

	const double p = find_longest_path((const double *)E, 5);
	cout << p << endl;
	return 0;
}


