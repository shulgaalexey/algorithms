// Dynamic Programming algs
// Examples considered:
// Fibonacci calculation with O(N)

#include <iostream>
using namespace std;


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

	// Fibonacci
	cout << endl << "Fibonacci numbers:" << endl;
	for(int i = 0; i < 10; i ++)
		cout << i << ": " << fibonacci(i) << endl;

	return 0;
}
