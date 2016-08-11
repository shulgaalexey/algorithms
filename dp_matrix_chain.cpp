// Dynamic Programming algs
// Examples considered:
// Matrix Chain Product problem
//

#include <iostream>
using namespace std;


void print_parens(int *s, const int i, const int j, int length) {
	if(i == j)
		cout << "A" << i;
	else {
		cout << "(";
		print_parens(s, i, s[i * length + j], length);
		cout << "*";
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
	// Matrix chain problem
	cout << "Matrix Chain Problem:" << endl;
	int p[] = {30, 35, 15, 5, 10, 20, 25};
	const int ret = matrix_chain(p, int(sizeof(p) / sizeof(p[0])));
	if(ret != 15125)
		cout << "Error Matrix Chain: " << ret << endl;
	else
		cout << ret << " OK" << endl;
	cout << "--------------------------" << endl << endl;

	return 0;
}
