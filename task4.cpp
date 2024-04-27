#include <iostream>

using namespace std;

// swap two elements
void swapElements(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

// array around a pivot k
void partitionAroundK(int array[], int low, int high, int pivot) {
    if (low >= high) return; // Base case

    int partitionIdx = low;
    
    // Move elements less than or equal to pivot to the left
    for (int i = low; i < high; i++) {
        if (array[i] <= pivot) {
            swapElements(array[i], array[partitionIdx]);
            partitionIdx++;
        }
    }
    swapElements(array[partitionIdx], array[high]);

    // arrange the left part if it contains elements <= pivot
    if (partitionIdx > low && array[partitionIdx - 1] <= pivot)
        partitionAroundK(array, low, partitionIdx - 1, pivot);
}


void displayArray(int array[], int length) {
    for (int i = 0; i < length; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

int main() {
    int data[] = {15, 22, 19, 28, 12, 14, 13, 16, 11, 18};
    int length = sizeof(data) / sizeof(data[0]);
    int pivot = 14;

    cout << "Original Array: ";
    displayArray(data, length);

    partitionAroundK(data, 0, length - 1, pivot);
    cout << "Rearranged Array: ";
    displayArray(data, length);

    return 0;
}
