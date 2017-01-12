#include <iostream>
#include <queue>
#include <climits>
using namespace std;

class point {
public:
	int x;
	int y;
	point() : x(0), y(0) {}
	point(int _x, int _y) : x(_x), y(_y) {}
	bool operator==(const point &p) {
		if (this == &p)
			return true;
		return ((p.x == x) && (p.y == y));
	}
	point north() const { return point(x, y - 1); }
	point east() const { return point(x + 1, y); }
	point south() const { return point(x, y + 1); }
	point west() const { return point(x - 1, y); }
};

void print(int *G, const int n, const int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			switch (G[i * m + j]) {
			case -1:
				cout << "# ";
				break;
			case -2:
				cout << "V ";
				break;
			case -3:
				cout << "> ";
				break;
			case INT_MAX:
				cout << "~ ";
				break;
			default:
				cout << G[i * m + j] << " ";
				break;
			}
		}
		cout << endl;
	}
	cout << endl;
}

void set_dist(int *G, const int n, const int m, const point &p, const int v)
{
	G[p.y * m + p.x] = v;
}

int get_dist(int *G, const int n, const int m, const point &p)
{
	return G[p.y * m + p.x];
}

bool obstacle(int *G, const int n, const int m, const point &p)
{
	//return (G[p.y * m + p.x] == (-1));
	return (G[p.y * m + p.x] < 0);
}

bool valid(const point &p, const int n, const int m)
{
	if (p.y < 0)
		return false;
	if (p.y >= n)
		return false;
	if (p.x < 0)
		return false;
	if (p.x >= m)
		return false;
	return true;
}

int calc_maze_dist(int *G, const int n, const int m,
		const point &start, const point &exit)
{
	// -1 - obstacle
	for (int i = 0; i < (n * m); i++)
		if (G[i] != (-1))
			G[i] = INT_MAX;

	// TODO check if exit is obstcke than return -1

	queue<point> q;
	q.push(start);
	set_dist(G, n, m, start, 0);
	while (!q.empty()) {
		point p = q.front();
		q.pop();
		int d = get_dist(G, n, m, p) + 1;

		point pnext = p.north();
		if (pnext == exit)
			return d;
		if (valid(pnext, n, m) && !obstacle(G, n, m, pnext) && (d < get_dist(G, n, m, pnext))) {
			q.push(pnext);
			set_dist(G, n, m, pnext, d);
		}


		pnext = p.east();
		if (pnext == exit)
			return d;
		if (valid(pnext, n, m) && !obstacle(G, n, m, pnext) && (d < get_dist(G, n, m, pnext))) {
			q.push(pnext);
			set_dist(G, n, m, pnext, d);
		}

		pnext = p.south();
		if (pnext == exit)
			return d;
		if (valid(pnext, n, m) && !obstacle(G, n, m, pnext) && (d < get_dist(G, n, m, pnext))) {
			q.push(pnext);
			set_dist(G, n, m, pnext, d);
		}

		pnext = p.west();
		if (pnext == exit)
			return d;
		if (valid(pnext, n, m) && !obstacle(G, n, m, pnext) && (d < get_dist(G, n, m, pnext))) {
			q.push(pnext);
			set_dist(G, n, m, pnext, d);
		}
	}
	return -1;
}

int main(void)
{
	const int n = 6;
	const int m = 5;
	int *G = new int [n * m];
	for (int i = 0; i < (n * m); i ++)
		G[i] = 0;

	G[1 * m + 1] = -1;
	G[2 * m + 1] = -1;
	G[3 * m + 2] = -1;
	G[5 * m + 2] = -1;

	const point enter(0, 0);
	const point exit(4, 3);
	//const point exit(2, 5);

	G[enter.y * m + enter.x] = -2;
	G[exit.y * m + exit.x] = -3;

	cout << "Initial maze:" << endl;
	print(G, n, m);

	cout << "Way length to exit: ";
	cout << calc_maze_dist(G, n, m, enter, exit) << endl << endl;

	cout << "Processed maze:" << endl;
	print(G, n, m);

	delete [] G;

	return 0;
}
