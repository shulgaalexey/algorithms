#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <climits>
//#include <exception>
using namespace std;

#define LEFT(i) (i * 2 + 1);
#define RIGHT(i) (i * 2 + 2);
#define PARENT(i) (int((i - 1) / 2))

class priority_queue {
	public:
		priority_queue(const int max_size);
		~priority_queue();
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
	private:
		int __max_size;
		int __cur_size;
		int *__buf;
};

priority_queue::priority_queue(const int max_size)
 : __max_size(max_size)
 , __cur_size(0) {
	if (__max_size <= 0)
		throw "Non-positive size of priority queue";
	__buf = new int[__max_size];
}

priority_queue::~priority_queue() {
	delete [] __buf;
}

void priority_queue::insert(const int x) {
	if (__cur_size == __max_size)
		throw "Priority Queue overflow";

	__buf[__cur_size] = INT_MIN;
	__cur_size++;
	increase(__cur_size - 1, x);
}

int priority_queue::max() const {
	if (__cur_size <= 0)
		throw "Priority queue is empty";
	return __buf[0];
}

int priority_queue::extract_max() {
	if (__cur_size < 0)
		throw "Priority queue is empty";
	const int ret = __buf[0];
	__cur_size--;
	if (__cur_size) {
		swap(0, __cur_size);
		max_heapify(0);
	}
	return ret;
}

void priority_queue::increase(int i, const int k) {
	if ((i < 0) || (i >= __cur_size))
		throw "Index is out of range";
	if (__buf[i] > k)
		throw "New values is smaller then the old one";

	__buf[i] = k;
	while ((i > 0) && (__buf[PARENT(i)] < __buf[i])) {
		swap(i, PARENT(i));
		i = PARENT(i);
	}
}

void priority_queue::remove(const int i) {
	if ((i < 0) || (i >= __cur_size))
		throw "Index is out of range";

	if (i == (__cur_size - 1)) {
		__cur_size--;
	} else {
		swap(i, __cur_size - 1);
		__cur_size--;
		max_heapify(i);
	}
}

bool priority_queue::empty() const {
	return (__cur_size <= 0);
}

void priority_queue::swap(const int i, const int j) {
	int tmp = __buf[i];
	__buf[i] = __buf[j];
	__buf[j] = tmp;
}

void priority_queue::max_heapify(const int i) {
	int largest = i;

	int l = LEFT(i);
	if ((l < __cur_size) && (__buf[l] > __buf[i]))
		largest = l;

	int r = RIGHT(i);
	if ((r < __cur_size) && (__buf[r] > __buf[largest]))
		largest = r;

	if (i != largest) {
		swap(i, largest);
		max_heapify(largest);
	}
}



int main(void) {

	{ // 0
		priority_queue pq(10);
		for (int i = 0; i < 5; i ++)
			pq.insert(i);
	}

	try { // 1
		priority_queue pq(10);
		for (int i = 0; i < 10; i ++) {
			const int v = rand() % 10;
			//const int v = i;
			pq.insert(v);
			cout << "Inserted: " << v << " [max: " << pq.max() << "]" << endl;
		}

		cout << "------" << endl;

		pq.increase(3, 15);

		cout << "------" << endl;

		pq.remove(4);
		pq.remove(5);

		cout << "------" << endl;

		//for (int i = 0; i < 10; i ++) {
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

