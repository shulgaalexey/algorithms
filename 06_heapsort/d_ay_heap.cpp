#include <iostream>
#include <climits>
#include <stdlib.h>
#include <time.h>

using namespace std;

class d_ary_heap {
public:
	d_ary_heap(const int d, const int max_size);
	~d_ary_heap();
public:
	void insert(const int x);
	int max() const;
	int extract_max();
	void increase(int i, const int k);
	void remove(const int i);
	bool empty() const;
private:
	void swap(const int i, const int j);
	void max_heapify(const int i);
	inline int CHILD(const int i, const int ch);
	inline int PARENT(const int i);
private:
	const int __d;
	const int __max_size;
	int __cur_size;
	int *__buf;
};

d_ary_heap::d_ary_heap(const int d, const int max_size)
 : __d(d)
 , __max_size(max_size)
 , __cur_size(0) {
	if (__max_size <= 0)
		throw "CTOR: Size of heap is non-positive";
	__buf = new int[__max_size];
}

d_ary_heap::~d_ary_heap() {
	delete [] __buf;
}

void d_ary_heap::insert(const int x) {
	if (__cur_size == __max_size)
		throw "INSERT: Heap overflow";
	__buf[__cur_size] = INT_MIN;
	__cur_size++;
	increase(__cur_size - 1, x);
}

int d_ary_heap::max() const {
	if (!__cur_size)
		throw "MAX: Heap is empty";
	return __buf[0];
}

int d_ary_heap::extract_max() {
	const int ret = max();
	__buf[0] = __buf[__cur_size - 1];
	__cur_size--;
	max_heapify(0);
	return ret;
}

void d_ary_heap::increase(int i, const int k) {
	if ((i < 0) || (i >= __cur_size))
		throw "INCREASE: Index is out of range";
	if (__buf[i] >= k)
		throw "INCREASE: New values is smaller then the old one";

	__buf[i] = k;
	while ((i > 0) && (__buf[PARENT(i)] < __buf[i])) {
		swap(i, PARENT(i));
		i = PARENT(i);
	}
}

void d_ary_heap::remove(const int i) {
	if ((i < 0) || (i >= __cur_size))
		throw "REMOVE: Index is out of range";

	swap(i, __cur_size - 1);
	__cur_size--;
	if (i != __cur_size)
		max_heapify(i);
}

bool d_ary_heap::empty() const {
	return __cur_size == 0;
}

void d_ary_heap::swap(const int i, const int j) {
	int tmp = __buf[i];
	__buf[i] = __buf[j];
	__buf[j] = tmp;
}

void d_ary_heap::max_heapify(const int i) {
	int largest = i;
	for (int d = 0; d < __d; d++)
		if((CHILD(i, d) < __cur_size) && (__buf[largest] < __buf[CHILD(i, d)]))
			largest = CHILD(i, d);

	if (largest != i) {
		swap(i, largest);
		max_heapify(largest);
	}
}

int d_ary_heap::CHILD(const int i, const int ch) {
	return (i * __d + ch + 1);
}

int d_ary_heap::PARENT(const int i) {
	return int((i - 1) / __d);
}

int main(void) {

	{ // 0
		d_ary_heap pq(2, 10);
		for (int i = 0; i < 5; i ++)
			pq.insert(i);
	}

	srand(time(NULL));

	try { // 1
		d_ary_heap pq(3, 20);
		for (int i = 0; i < 20; i ++) {
			const int v = rand() % 10;
			//const int v = i;
			pq.insert(v);
			cout << "Inserted: " << v << " [max: " << pq.max() << "]" << endl;
		}

		cout << "------" << endl;

		cout << "Increased item 3 to 15" << endl;
		pq.increase(3, 15);

		cout << "------" << endl;

		pq.remove(4);
		pq.remove(5);

		cout << "------" << endl;

		while (!pq.empty()) {
			const int v = pq.extract_max();
			cout << "Extracted: " << v << " [max: ";
			if (!pq.empty())
				cout << pq.max();
			else
				cout << "empty queue";
			cout << "]" << endl;
		}

	} catch(char const *e) {
		cout << e << endl;
	}

	return 0;
}

