// max heap implementation in c++
// can be used to efficiently implement
// a priority queue

#include <iostream>
#include <vector>
#include <cassert>

using std::vector;
using std::cout;
using std::endl;

class MaxHeap {
	private:
		int _size{};
		vector<int> vec = {-1};
		
		int parent(int i) { return i>>1; };
		int leftChild(int i) { return i<<1; };
		int rightChild(int i) { return (i<<1) + 1; };
		
	public:
		bool isEmpty() const { return _size == 0; };
		int getMax() const { return vec[1]; };
		void insert(int val);
		void shiftUp(int i);
		void shiftDown(int i);
		int popMax();
};

void MaxHeap::shiftUp(int i) {
	if (i > _size) return;
	if (i == 1) return;
	
	int p = parent(i);
	if (vec[i] > vec[p]) {
		std::swap(vec[p], vec[i]);
	}
	shiftUp(p);
}

void MaxHeap::shiftDown(int i) {
	if (i > _size) return;
	
	int swapId = i;
	int l = leftChild(i);
	int r = rightChild(i);
	
	if (l <= _size && vec[i] < vec[l]) {
		swapId = l;
	}
	if (r <= _size && vec[i] < vec[r]) {
		swapId = r;
	}
	
	if (swapId != i) {
		std::swap(vec[i], vec[swapId]);
		shiftDown(swapId);
	}
	return;
}

int MaxHeap::popMax() {
	int maxVal = vec[1];
	std::swap(vec[1], vec[_size--]);
	shiftDown(1);
	return maxVal;
}

void MaxHeap::insert(int val) {
	if (_size + 1 >= int(vec.size())) {
		vec.push_back(0);
	}
	vec[++_size] = val;
	shiftUp(_size);
	return;
}

int main() {
	MaxHeap* PriorityQueue = new MaxHeap();
	
	assert(PriorityQueue->isEmpty());

	PriorityQueue->insert(5);
	PriorityQueue->insert(15);
	PriorityQueue->insert(2);
	PriorityQueue->insert(21);
	PriorityQueue->insert(8);
	PriorityQueue->insert(19);
	
	assert(PriorityQueue->getMax() == 21);
	
	PriorityQueue->popMax();
	
	assert(PriorityQueue->getMax() == 19);
	
	assert(!PriorityQueue->isEmpty());
	
	cout << "Tests correctly passed" << endl;
	
	return 0;
	
}
