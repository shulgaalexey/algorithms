//15-3 Bitonic euclidean traveling-salesman problem
//In the euclidean traveling-salesman problem, we are given a set of n points in
//the plane, and we wish to find the shortest closed tour that connects all n points.
//Figure 15.11(a) shows the solution to a 7-point problem. The general problem is
//NP-hard, and its solution is therefore believed to require more than polynomial
//time (see Chapter 34).
//J. L. Bentley has suggested that we simplify the problem by restricting our at-
//tention to bitonic tours, that is, tours that start at the leftmost point, go strictly
//rightward to the rightmost point, and then go strictly leftward back to the starting
//point. Figure 15.11(b) shows the shortest bitonic tour of the same 7 points. In this
//case, a polynomial-time algorithm is possible.
//Describe an O.n 2 /-time algorithm for determining an optimal bitonic tour. You
//may assume that no two points have the same x-coordinate and that all operations
//on real numbers take unit time. (Hint: Scan left to right, maintaining optimal pos-
//sibilities for the two parts of the tour.)

#include <iostream>
#include <stack>
#include <math.h>
using namespace std;

void bitonic_tsp(int *p, int *y, const int n) {
	double l[n][n] = {0};
	int N[n][n] = {0};
	double dist[n][n] = {0};

	// Calc the distances
	for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++) {
			if(i == j)
				continue;
			int a = p[i] - p[j];
			a *= a;
			int b = y[i] - y[j];
			b *= b;
			dist[i][j] = sqrt(a + b);
			cout << i << "," << j << ":" << dist[i][j] << endl;
		}
	}

	// Calc the route
	for(int j = 1; j < n; j ++) {
		for(int i = 0; i <= (j - 1); i ++) {
			if((i == 0) && (j == 1)) {
				l[i][j] = dist[i][j];
				N[i][j] = i;
			} else if(j > (i + 1)) {
				l[i][j] = l[i][j - 1] + dist[j - 1][j];
				N[i][j] = j - 1;
			} else {
				l[i][j] = 1000000;
				int q = 0;
				for(int k = 0; k < (i - 1); k ++) {
					q = l[k][i] + dist[k][j];
					if(q < l[i][j]) {
						l[i][j] = q;
						N[i][j] = k;
					}
				}
			}
		}
	}

	// Reconstruct the route
	stack<int> S[2];
	int k = 0;
	int i = n - 2;
	int j = n - 1;
	while(j > 0) {
		S[k].push(j);
		j = N[i][j];
		if(j < i) {
			int tmp = i;
			i = j;
			j = tmp;
			if(k == 0)
				k = 1;
			else
				k = 0;
		}
	}

	S[0].push(0);
	while(!S[1].empty()) {
		S[0].push(S[1].top());
		S[1].pop();
	}

	while(!S[0].empty()) {
		cout << S[0].top() << endl;
		S[0].pop();
	}
}

int main(void) {

	int x[] = {1, 2, 3, 6, 7, 8, 9};
	int y[] = {1, 7, 4, 3, 6, 2, 5};
	const int n = int(sizeof(x) / sizeof(x[0]));
	bitonic_tsp(x, y, n);
	return 0;
}
