// 15-2 Longest palindrome subsequence
// A palindrome is a nonempty string over some alphabet that reads the same for-
// ward and backward. Examples of palindromes are all strings of length 1, civic,
// racecar, and aibohphobia (fear of palindromes).
// Give an efficient algorithm to find the longest palindrome that is a subsequence
// of a given input string. For example, given the input character, your algorithm
// should return carac. What is the running time of your algorithm?

#include <iostream>
#include <string.h>
using namespace std;

int find_longest_palindrome_length(const char *S) {
	const int n = strlen(S);
	int L[n][n] = {0};

	for(int i = 0; i < n; i ++)
		L[i][i] = 1;

	for(int d = 1; d < n; d ++) {
		for(int i = 0; i < (n - d); i ++) {
			int j = i + d;

			if(S[i] == S[j])
				L[i][j] = L[i + 1][j - 1] + 2;
			else
				L[i][j] = max(L[i][j - 1], L[i + 1][j]);
		}

	}

	/*for(int i = 0; i < n; i ++) {
		for(int j = 0; j < n; j ++)
			cout << L[i][j] << " ";
		cout << endl;
	}
	cout << endl;*/

	return L[0][n - 1];
}

int main(void) {
	{ // 1
		const int l = find_longest_palindrome_length("character");
		cout << l << endl;
		if(l != 5)
			cout << "ERROR" << endl;
	}

	{ // 2
		const int l = find_longest_palindrome_length("charracter");
		cout << l << endl;
		if(l != 6)
			cout << "ERROR2" << endl;
	}

	{ // 3
		const int l = find_longest_palindrome_length("abcdcba");
		cout << l << endl;
		if(l != 7)
			cout << "ERROR3" << endl;
	}

	{ // 4
		const int l = find_longest_palindrome_length("abcddcba");
		cout << l << endl;
		if(l != 8)
			cout << "ERROR4" << endl;
	}

	{ // 5
		const int l = find_longest_palindrome_length("12345character");
		cout << l << endl;
		if(l != 5)
			cout << "ERROR5" << endl;
	}

	{ // 6
		const int l = find_longest_palindrome_length("12345character6789");
		cout << l << endl;
		if(l != 5)
			cout << "ERROR6" << endl;
	}


	return 0;
}
