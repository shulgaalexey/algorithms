#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

class edge {
public:
	char from;
	char to;
	int w;
	edge(char f, char t, int _w) : from(f), to(t), w(_w) {}
};

bool edgesort(edge a, edge b)
{
	return a.w < b.w;
}

vector<edge> min_spanning_tree(const vector<char> &V, vector<edge> &E)
{
	map<char, set<char> *> parts;
	vector<set<char> *> __PPOOL;
	for (size_t i = 0; i < V.size(); i++) {
		set<char> *p = new set<char>();
		p->insert(V[i]);
		parts[V[i]] = p;
		__PPOOL.push_back(p);
	}

	std::sort(E.begin(), E.end(), edgesort);

	vector<edge> spanning_tree;
	for (size_t i = 0; i < E.size(); i++) {
		const edge e = E[i];
		set<char> *pfrom = parts[e.from];
		set<char> *pto = parts[e.to];
		if (pfrom != pto) {
			spanning_tree.push_back(e);
			if (pfrom->size() < pto->size()) {
				for (set<char>::iterator it = pfrom->begin();
						it != pfrom->end(); ++it) {
					pto->insert(*it);
					parts[*it] = pto;
				}
			} else {
				for (set<char>::iterator it = pto->begin();
						it != pto->end(); ++it) {
					pfrom->insert(*it);
					parts[*it] = pfrom;
				}
			}
		}
	}

	for (size_t i = 0; i < __PPOOL.size(); i++)
		delete __PPOOL[i];

	return spanning_tree;
}

int main(void)
{
	vector<char> V;
	for (char ch = 'a'; ch <= 'i'; ch++)
		V.push_back(ch);

	vector<edge> E;
	E.push_back(edge('a', 'b', 4));
	E.push_back(edge('a', 'h', 8));
	E.push_back(edge('b', 'h', 11));
	E.push_back(edge('b', 'c', 8));
	E.push_back(edge('c', 'i', 2));
	E.push_back(edge('c', 'd', 7));
	E.push_back(edge('c', 'f', 4));
	E.push_back(edge('d', 'e', 9));
	E.push_back(edge('d', 'f', 14));
	E.push_back(edge('e', 'f', 10));
	E.push_back(edge('g', 'f', 2));
	E.push_back(edge('g', 'h', 1));

	vector<edge> MST = min_spanning_tree(V, E);

	int total = 0;
	for (size_t i = 0; i < MST.size(); i++) {
		cout << MST[i].from << ", " << MST[i].to << endl;
		total += MST[i].w;
	}
	cout << "total: " << total << endl;

	return 0;
}

