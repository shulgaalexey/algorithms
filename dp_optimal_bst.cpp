// Implementation of Optimal Binary Search Tree
// using Dynamic Programmin
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > levels(6);

void reconstr(int *root, int i, int j, int n, int level) {
	if((j < i) || (i > j))
		return;
	const int r = root[i * n + j];
	levels[level].push_back(r);
	reconstr(root, i, r - 1, n, level + 1);
	reconstr(root, r + 1, j, n, level + 1);
}

double optimal_bst(const double *p, const double *q, const int n) {
	double e[n + 2][n + 1] = {0};
	double w[n + 2][n + 1] = {0};
	int root[n + 1][n + 1] = {0};

	for(int i = 1; i <= (n + 1); i ++) {
		e[i][i -1] = q[i - 1];
		w[i][i -1] = q[i - 1];
	}

	for(int l = 1; l <= n; l ++) {
		for(int i = 1; i <= (n - l + 1); i ++) {
			const int j = i + l - 1;
			e[i][j] = 1000000.;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			for(int r = i; r <= j; r ++) {
				double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
				if(t < e[i][j]) {
					e[i][j] = t;
					root[i][j] = r;
				}
			}
		}
	}

	// reconstructing the tree
	/*for(int i = 0; i <= n; i ++) {
		for(int j = 0; j <= n; j ++) {
			cout << root[i][j] << " ";
		}
		cout << endl;
	}*/

	reconstr((int *)root, 1, n, n + 1, 0);
	for(size_t i = 0; i < levels.size(); i ++) {
		for(size_t j = 0; j < levels[i].size(); j ++) {
			cout << levels[i][j] << " ";
		}
		if(!levels[i].empty())
			cout << endl;
	}

	return e[1][n];
}

int main(void) {
	double p[] = {0.00, 0.15, 0.10, 0.05, 0.10, 0.20};
	double q[] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
	const int n = 5;
	const double c = optimal_bst(p, q, n);
	cout << c << endl;
	if(c != 2.75)
		cout << "ERROR" << endl;
	return 0;
}

