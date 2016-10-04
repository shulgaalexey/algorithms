// 15-5 Edit distance
// In order to transform one source string of text x[1..m] to a target string y[1..n],
// we can perform various transformation operations. Our goal is, given x and y,
// to produce a series of transformations that change x to y. We use an ar-
// ray  ́—assumed to be large enough to hold all the characters it will need—to hold
// the intermediate results. Initially,  ́ is empty, and at termination, we should have
// z[j] = y[j] for j = 1, 2, ... , n. We maintain current indices i into x and j into,
// and the operations are allowed to alter  ́ and these indices. Initially, i = j = 1.
// We are required to examine every character in x during the transformation, which
// means that at the end of the sequence of transformation operations, we must have
// i = m + 1.
// We may choose from among six transformation operations:
// Copy a character from x to  ́ by setting z[j] = x[i] and then incrementing both i
// and j . This operation examines x[i].
// Replace a character from x by another character c, by setting z[j] = c, and then
// incrementing both i and j . This operation examines x[i].
// Delete a character from x by incrementing i but leaving j alone. This operation
// examines x[i].
// Insert the character c into z by setting z[j] = c and then incrementing j , but
// leaving i alone. This operation examines no characters of x.
// Twiddle (i.e., exchange) the next two characters by copying them from x to z but
// in the opposite order; we do so by setting z[j] = x[i + 1] and a[j + 1] = x[i]
// and then setting i = i + 2 and j = j + 2. This operation examines x[i]
// and x[i + 1].
// Kill the remainder of x by setting i = m + 1. This operation examines all char-
// acters in x that have not yet been examined. This operation, if performed, must
// be the final operation.
//
// Given two sequences x[1 .. m] and y[1 .. n] and set of transformation-operation
// costs, the edit distance from x to y is the cost of the least expensive operation
// sequence that transforms x to y. Describe a dynamic-programming algorithm
// that finds the edit distance from x[1 .. m] to y[1 .. n] and prints an optimal op-
// eration sequence. Analyze the running time and space requirements of your
// algorithm.

#include <iostream>
#include <climits>
#include <string.h>
using namespace std;

enum Operations {
	COPY = 0,
	REPLACE,
	DELETE,
	INSERT,
	TWIDDLE,
	KILL
};

static const int cost[] =
	//{1, 3, 5, 5, 0, 10};
	//{1, 1, 3, 4, 5, 6};
	{0, 1, 1, 1, 5, 10};

int get_min(const int a0, const int a1, const int a2,
		const int a3, const int a4) {
	int arr[] = {a0, a1, a2, a3, a4};
	int min = arr[0];
	for(int i = 1; i < 5; i ++)
		if(arr[i] < min)
			min = arr[i];

	return min;
}

int get_edit_distance(const char *s1, const int m,
		const char *s2, const int n) {

	int dp[m + 1][n + 1] = {0};

	// First row and column
	for(int i = 1; i <= m; i ++)
		dp[i][0] = i * cost[DELETE];

	for(int j = 1; j <= n; j ++)
		dp[0][j] = j * cost[INSERT];

	// General cost calculation
	for(int i = 1; i <= m; i ++) {
		for(int j = 1; j <= n; j ++) {
			const int copy_cost = (s1[i - 1] == s2[j - 1])
				? (dp[i - 1][j - 1] + cost[COPY])
				: INT_MAX;

			const int replace_cost = dp[i - 1][j - 1] + cost[REPLACE];
			const int delete_cost = dp[i - 1][j] + cost[DELETE];
			const int insert_cost = dp[i][j - 1] + cost[INSERT];

			const bool twiddle_enable = (i > 1) && (j > 1) &&
				(s1[i - 1] == s2[j - 2]) &&
				(s1[i - 2] == s2[j - 1]);
			const int twiddle_cost = (twiddle_enable)
				? (dp[i - 2][j - 2] + cost[TWIDDLE])
				: INT_MAX;

			dp[i][j] = get_min(copy_cost,
					replace_cost,
					delete_cost,
					insert_cost,
					twiddle_cost);
		}
	}

	// Checking if "Kill" operation is giving benefits
	int min_idx = 1;
	for(int i = 1; i < m; i ++)
		if(dp[i][n] < dp[min_idx][n])
			min_idx = i;

	if((dp[min_idx][n] + cost[KILL]) < dp[m][n])
		dp[m][n] = dp[min_idx][n] + cost[KILL];

	return dp[m][n];
}

int main(void) {
	const char *s1 = "algorithm";
	const char *s2 = "altruistic";

	const int ret = get_edit_distance(s1, strlen(s1), s2, strlen(s2));
	cout << ret << endl;
	return 0;
}
