#include<iostream>
#include<algorithm>
#include<vector>
#include<limits>
using namespace std;

int parent(int i) {
	return (i - 1) / 2;
}

int left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}

vector<int> merge(const vector<int>& heap_1, const vector<int>& heap_2, int x) {
	vector<int> merged_heap = { x,heap_1[0], heap_2[0] };
	int max_size = max((int)heap_1.size(), (int)heap_2.size());
	for (int i = 0; i < max_size; ++i) {
		if (left(i) < heap_1.size()) {
			merged_heap.push_back(heap_1[left(i)]);
		}
		if (right(i) < heap_1.size()) {
			merged_heap.push_back(heap_1[right(i)]);
		}
		if (left(i) < heap_2.size()) {
			merged_heap.push_back(heap_2[left(i)]);
		}
		if (right(i) < heap_2.size()) {
			merged_heap.push_back(heap_2[right(i)]);
		}
	}
	return merged_heap;
}

int count_compares = 0;

vector<int> floyd_algorithm(const vector<int>& heap_1, const vector<int>& heap_2, int x) {
	vector<int> new_heap = merge(heap_1, heap_2, x);
	int i = 0;
	while (new_heap[i] <= new_heap[left(i)] || new_heap[i] <= new_heap[right(i)]) {
		count_compares += 3;
		int l = left(i);
		int r = right(i);
		int largest;
		if (l < new_heap.size() && new_heap[l] > new_heap[r]) {
			largest = l;
		}
		else {
			largest = r;
		}
		swap(new_heap[i], new_heap[largest]);
		i = largest;
	}
	return new_heap;
}

vector<int> building_heap_fast(const vector<int>& heap_1, const vector<int>& heap_2, int x) {
	vector<int> new_heap = merge(heap_1, heap_2, INT32_MIN);
	int i = 0;
	// trickle-down phase
	while (i < new_heap.size() / 2) {
		count_compares++;
		int l = left(i);
		int r = right(i);
		int largest;
		if (l < new_heap.size() && new_heap[l] > new_heap[r]) {
			largest = l;
		}
		else {
			largest = r;
		}
		swap(new_heap[i], new_heap[largest]);
		i = largest;
	}
	new_heap[i] = x;
	// bubble-up phase
	while (i != 0 && new_heap[i] > new_heap[parent(i)]) {
		count_compares++;
		swap(new_heap[i], new_heap[parent(i)]);
		i = parent(i);
	}
	count_compares++;
	return new_heap;
}

int main() {
	setlocale(LC_ALL, "ru");

	vector<int> heap_1 = { 10,8,4,1,2,3 };
	vector<int> heap_2 = { 9,6,7 };
	int x = 5;

	vector<int> heap = building_heap_fast(heap_1, heap_2, x);

	cout << "Количество сравнений в новом алгоритме: " << count_compares << endl;
	for (auto i : heap) {
		cout << i << " ";
	}
	cout << endl;

	count_compares = 0;

	heap = floyd_algorithm(heap_1, heap_2, x);

	cout << "Количество сравнений в алгоритме Флойда: " << count_compares << endl;
	for (auto i : heap) {
		cout << i << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}