#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent]) {
                swap(heap[index], heap[parent]);
                index = parent;
            } else {
                break;
            }
        }
    }

    void heapifyDown(int index) {
        int size = heap.size();
        while (index < size) {
            int left = 2 * index + 1;
            int right = 2 * index + 2;
            int largest = index;

            if (left < size && heap[left] > heap[largest])
                largest = left;
            if (right < size && heap[right] > heap[largest])
                largest = right;

            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

public:
    void insert(int val) {
        heap.push_back(val);
        heapifyUp(heap.size() - 1);
    }

    void deleteMax() {
        if (heap.empty()) {
            cout << "Heap is empty.\n";
            return;
        }
        cout << "Deleted element: " << heap[0] << endl;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    void display() {
        cout << "Heap (Level Order): ";
        for (int val : heap)
            cout << val << " ";
        cout << endl;
    }

    void displayMenu() {
        cout << "\n========== Max Heap Menu ==========\n";
        cout << "1. Insert\n";
        cout << "2. Delete Max (Root)\n";
        cout << "3. Display Heap (Level Order)\n";
        cout << "0. Exit\n";
        cout << "===================================\n";
        cout << "Enter your choice: ";
    }
};

int main() {
    MaxHeap heap;
    int choice, value;

    do {
        heap.displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            heap.insert(value);
            break;
        case 2:
            heap.deleteMax();
            break;
        case 3:
            heap.display();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 0);

    return 0;
}
