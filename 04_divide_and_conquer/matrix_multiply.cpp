#include <iostream>
using namespace std;

const int n = 3;

int A[n][n] = { {1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}};

int B[n][n] = { {9, 8, 7},
		{6, 5, 4},
		{3, 2, 1}};

int C[n][n] = {0};

int E[n][n] = { {30,   24, 18},
		{84,   69, 54},
		{138, 114, 90}};

void square_matrix_multiply() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int c = 0;
			for (int k = 0; k < n; k++)
				c += A[i][k] * B[k][j];
			C[i][j] = c;
		}
	}
}

int main(void) {
	square_matrix_multiply();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << C[i][j] << " ";
		cout << endl;
	}

	return 0;
}
