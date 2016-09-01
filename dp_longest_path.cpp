// Suppose that we are given a directed acyclic graph G = (V, E) with realvalued
// edge weights and two distinguished vertices s and t.
// Describe a dynamicprogramming
// approach for finding a longest weighted simple path from s to t.
// What does the subproblem graph look like? What is the efficiency of your algorithm?
#include <iostream>
using namespace std;

#define INF -1

//
// P[i,j] = max<P[i,j], P[i,l] + P[l,j]>
//
// DP: processing diagonals of the matrix, one-by-one
//
int find_longest_path(const int *E, const int n) {
	double P[n][n] = {0}; // table with paths calculated


	// initialization
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < n; j ++)
			P[i][j] = E[i * n + j];

	/*cout << endl;
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++) {
			if(P[i][j] < 0)
				cout << "I ";
			else
				cout << P[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	// DP
	// Upper triangle of the matrix
	for(int j = 2; j < n; j ++) {
		for(int i = 0; i < j; i ++) {
			for(int l = (i + 1); l < j; l ++) {
				if((P[i][j - 1] != INF) && (P[i + 1][j] != INF)) {
					P[i][j] = max(P[i][j], P[i][j - 1] + P[i + 1][j]);
				}
			}
		}

	}


	// DP
	// Lower triangle of the matrix
	for(int i = 2; i < n; i ++) {
		for(int j = 0; j < (i - 1); j ++) {
			for(int l = (j + 1); l < j; l ++) {
				if((P[i - 1][j] != INF) && (P[i][j + 1] != INF)) {
					P[i][j] = max(P[i][j], P[i - 1][j] + P[i][j + 1]);
				}
			}
		}
	}

	/*for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++) {
			if(P[i][j] < 0)
				cout << "I ";
			else
				cout << P[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;*/

	return P[0][n - 1];
}

int main(void) {
	const int E[5][5] = {
		0,   1,   3,   5,   8,
		INF, 0,   8,   INF, 2,
		INF, INF, 0,   INF, 4,
		INF, INF, 9,   0,   7
		INF, INF, INF, INF, 0
	};

	const int p = find_longest_path((const int *)E, 5);
	cout << p << endl;
	if(p != 8)
		cout << "ERROR" << endl;
	return 0;
}


