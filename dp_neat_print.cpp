// 15-4 Printing neatly
// Consider the problem of neatly printing a paragraph with a monospaced font (all
// characters having the same width) on a printer. The input text is a sequence of
// words of lengths l1, l2, ... ln , measured in characters. We want to print this para-
// graph neatly on a number of lines that hold a maximum of M characters each. Our
// criterion of “neatness” is as follows. If a given line contains words i through j,
// where i <= j, and we leave exactly one space between words, the number of extra
// space characters at the end of the line is M - j + i  E<k = i..j>l[k] , which must be
// nonnegative so that the words fit on the line. We wish to minimize the sum, over
// all lines except the last, of the cubes of the numbers of extra space characters at the
// ends of lines. Give a dynamic-programming algorithm to print a paragraph of n
// words neatly on a printer. Analyze the running time and space requirements of
// your algorithm.
//
// http://www-bcf.usc.edu/~shanghua/teaching/Spring2010/public_html/files/HW3_Solutions_A.pdf

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

//const int M = 25;
const int M = 45;

int print_lines(int *p, int j, const vector<string> &text) {
	int i = p[j];
	int k = 0;
	if(i == 1)
		k = 1;
	else
		k = print_lines(p, i - 1, text) + 1;

	//cout << "line " << k << ": ";
	for(int m = (i - 1); m < j; m ++)
		cout << text[m] << " ";
	cout << endl;

	return k;
}

void neat_print(const vector<string> &text) {
	const int n = int(text.size());

	int l[n] = {0};
	for(int i = 0; i < n; i ++)
		l[i] = int(text[i].length());

	// Compute extras (remaining spaces in the lines)
	int extras[n][n] = {0};
	for(int i = 0; i < n; i ++) {
		extras[i][i] = M - l[i];
		for(int j = (i + 1); j < n; j ++) {
			extras[i][j] = extras[i][j - 1] - l[j] - 1;
		}
	}

	// Compute each line cost
	int lc[n][n] = {0};
	for(int i = 0; i < n; i ++) {
		for(int j = i; j < n; j ++) {
			if(extras[i][j] < 0)
				lc[i][j] = 1000000;
			else if((j == (n - 1)) && (extras[i][j] >= 0))
				lc[i][j] = 0;
			else
				lc[i][j] = extras[i][j] * extras[i][j] * extras[i][j];
		}
	}

	// Compute line breakes
	int c[n + 1] = {0};
	int p[n + 1] = {0};
	for(int j = 1; j <= n; j ++) {
		c[j] = 1000000;
		for(int i = 1; i <= j; i ++) {
			int cur = c[i - 1] + lc[i - 1][j - 1];
			if(cur < c[j]) {
				c[j] = cur;
				p[j] = i;
			}
		}
	}

	// Actually printing the text
	cout << endl;
	cout << "------------------------------------" << endl;
	print_lines(p, n, text);
	cout << "------------------------------------" << endl;
	cout << endl;
}

static string trim(const string &input) {
	string str = input;
	stringstream trimmer;
	trimmer << str;
	str.clear();
	trimmer >> str;
	return str;
}

static void tokenize(const string &input, vector<string> *cmd) {

	stringstream ss(input);
	string word;
	while (ss >> word) {
		cmd->push_back(trim(word));
	}
}


int main(void) {
	string str = "Consider the problem of neatly printing a paragraph on a printer. The input text is a sequence of n words of lengths l1,l2,...,ln, measured in characters. We want to print this paragraph neatly on a number of lines that hold a maximum of M characters each. Our criterion of 'neatness, is as follows. If a given line contains words i through j and we leave exactly one space between words, the number of extra space characters at the end of the line is the difference between M and the total number of characters in the words plus the spaces between them .We wish to minimize the sum, over all lines except the last, of the cubes of the numbers of extra space characters at the ends of lines. Give a dynamic-programming algorithm to print a paragraph of n words neatly on a printer. Analyze the running time and space requirements of your algorithm.";


	/*string str =
		"Consider the problem of neatly printing a paragraph with a monospaced font (all"
		" characters having the same width) on a printer.";
		*/
	vector<string> text;
	tokenize(str, &text);

	//for(size_t i = 0; i < text.size(); i ++)
	//	cout << text[i] << endl;


	neat_print(text);

	return 0;
}
