// Dynamic Programming algs
// Examples considered:
// Longest Common Sequence problem

#include <iostream>
#include <string.h>
using namespace std;

void print_lcs(int *b, const char *X, const int i, const int j, const int n) {
	if((i == 0) || (j == 0))
		return;
	/*switch(b[i * n + j]) {
		case 1:
			print_lcs(b, X, i - 1, j - 1, n);
			cout << X[i];
			break;
		case 2:
			print_lcs(b, X, i - 1, j, n);
			break;
		case 3:
			print_lcs(b, X, i, j - 1, n);
			break;
		default:
			cout << "E";
	}*/
	if(b[i * n + j] == 1) {
		print_lcs(b, X, i - 1, j - 1, n);
		cout << X[i];
	} else if(b[i * n + j] == 2)
		print_lcs(b, X, i - 1, j, n);
	else
		print_lcs(b, X, i, j - 1, n);
}

void print_lcs_with_no_b(int *c, const char *X, const int i, const int j, const int n) {
	if((i == 0) || (j == 0))
		return;

	const int cur = c[i * n + j];
	const int top = c[(i - 1) * n + j];
	const int left = c[i * n + j - 1];
	const int topleft = c[(i - 1) * n + j - 1];

	if((cur == top) && (top >= left)) {
		print_lcs_with_no_b(c, X, i - 1, j, n); // to the top
	} else if(cur == (topleft + 1)) {
		print_lcs_with_no_b(c, X, i - 1, j - 1, n); // to the top-left
		cout << X[i];
	} else {
		print_lcs_with_no_b(c, X, i, j - 1, n); // to the left
	}
}

int lcs_length(const char *X, const char *Y, const int m, const int n) {
	int b[m + 1][n + 1]; // for reconstructing the LCS
	int c[m + 1][n + 1]; // lengths

	for(int i = 1; i <= m; i ++) {
		b[i][0] = 0;
		c[i][0] = 0;
	}
	for(int j = 0; j <= n; j ++) {
		b[0][j] = 0;
		c[0][j] = 0;
	}

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
			if(i == 0) {
				cout << Y[j] << " ";
				continue;
			}
			if(j == 0) {
				cout << X[i] << " ";
				continue;
			}

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

	print_lcs_with_no_b((int *)c, X, m, n, n + 1);
	cout << endl;

	print_lcs((int *)b, X, m, n, n + 1);
	cout << endl;

	return c[m][n];
}

int main(void) {

	{ // Test 1
		const char *X = " ABCBDAB";
		const char *Y = " BDCABA";
		const int l = lcs_length(X, Y, strlen(X) - 1, strlen(Y) - 1);
		if(l != 4)
			cout << "ERROR" << endl;
		else
			cout << l << " OK" << endl;
	}

	cout << endl;

	{ // Test 2
		const char *X = " 10010101";
		const char *Y = " 010110110";
		const int l = lcs_length(X, Y, strlen(X) - 1, strlen(Y) - 1);
		cout << l << endl;
	}

	return 0;
}
