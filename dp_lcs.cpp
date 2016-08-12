// Dynamic Programming algs
// Examples considered:
// Longest Common Sequence problem

#include <iostream>
#include <string.h>
using namespace std;

void print_lcs(int *b, const char *X, const int i, const int j, const int m) {
	if((i == 0) || (j == 0))
		return;
	if(b[i * m + j] == 1) {
		print_lcs(b, X, i - 1, j - 1, m);
		cout << X[i];
	} else if(b[i * m + j] == 2)
		print_lcs(b, X, i - 1, j, m);
	else
		print_lcs(b, X, i, j - 1, m);
}

int lcs_length(const char *X, const char *Y, const int m, const int n) {
	int b[m + 1][n + 1]; // for reconstructing the LCS
	int c[m + 1][n + 1]; // lengths

	for(int i = 1; i <= m; i ++)
		c[i][0] = 0;
	for(int j = 0; j <= n; j ++)
		c[0][j] = 0;

	for(int i = 1; i <= m; i ++) {
		for(int j = 1; j <= n; j ++) {
			if(X[i] == Y[j]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1; // move top-left
			} else if(c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
				b[i][j] = 2; // move top
			} else {
				c[i][j] = c[i][j - 1];
				b[i][j] = 3; // move left
			}
		}
	}

#if 0
	// Dbg tracing
	for(int i = 0; i <= m; i ++) {
		for(int j = 0; j <= n; j ++) {
			cout << c[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	for(int i = 0; i <= m; i ++) {
		for(int j = 0; j <= n; j ++) {
			switch(b[i][j]) {
				case 1: cout << "\\ "; break;
				case 2: cout << "| "; break;
				case 3: cout << "- "; break;
				default: cout << "# "; break;
			}
		}
		cout << endl;
	}
	cout << endl;
#endif

	print_lcs((int *)b, X, m, n, m);
	cout << endl;

	return c[m][n];
}

int main(void) {


	const char *X = " ABCBDAB";
	const char *Y = " BDCABA";
	const int l = lcs_length(X, Y, strlen(X) - 1, strlen(Y) - 1);
	if(l != 4)
		cout << "ERROR" << endl;
	else
		cout << l << " OK" << endl;
	return 0;
}
