#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>

using namespace std;
ofstream graphsfile("graphs_sort.csv");

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}


int bubblesorting(vector<int>& arr, int &time) {
    int count = 0;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < arr.size() - 1; i++) {
        for (int j = 0; j < arr.size() - i - 1; j++) {
            count++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
    auto stop = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return count;
}


int selectionsorting(vector<int>& arr, int &time) {
    int count = 0;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < arr.size() - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < arr.size(); j++) {
            count++;
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        swap(arr[i], arr[min_idx]);
    }
    auto stop = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return count;
}

int insertionsorting(vector<int>& arr, int &time) {
    int count = 0;
    auto start = chrono::high_resolution_clock::now();
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
            count++;
        }
        if (j >= 0) count++;
        arr[j + 1] = key;
    }
    auto stop = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return count;
}


void heapify(vector<int>& arr, int n, int i, int& count) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n) {
        count++;
        if (arr[l] > arr[largest])
            largest = l;
    }
    if (r < n) {
        count++;
        if (arr[r] > arr[largest])
            largest = r;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, count);
    }
}


int heapsorting(vector<int>& arr, int &time) {
    int count = 0;
    auto start = chrono::high_resolution_clock::now();
    for (int i = arr.size() / 2 - 1; i >= 0; i--)
        heapify(arr, arr.size(), i, count);
    for (int i = arr.size() - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, count);
    }
    auto stop = chrono::high_resolution_clock::now();
    time = chrono::duration_cast<chrono::microseconds>(stop - start).count();
    return count;
}


void comparisons() {
    graphs_file << "Size,Type,Sort,Comparisons,Time (µs)\n";
    cout << "Size,Type,Sort,Comparisons,Time (µs)\n";
    for (int size = 1; size <= 30; size++) {
        vector<int> random_array(size), sorted_array(size), reverse_array(size);

        
        for (int j = 0; j < size; j++) {
            random_array[j] = rand() % 100;
            sorted_array[j] = j;
            reverse_array[j] = size - j;
        }

        
        int comparisons, time;

        
        vector<int> temp;
        for (int k = 0; k < 3; k++) {  // 0 for random, 1 for sorted, 2 for reversed
            switch (k) {
                case 0: temp = random_array; break;
                case 1: temp = sorted_array; break;
                case 2: temp = reverse_array; break;
            }
            string type = (k == 0 ? "Random" : (k == 1 ? "Sorted" : "Reversed"));

            comparisons = bubble_sort_count(temp, time);
            graphs_file << size << "," << type << ",Bubble," << comparisons << "," << time << "\n";
            cout << size << "," << type << ",Bubble," << comparisons << "," << time << "\n";
            comparisons = selection_sort_count(temp, time);
            graphs_file << size << "," << type << ",Selection," << comparisons << "," << time << "\n";
            cout << size << "," << type << ",Selection," << comparisons << "," << time << "\n";
            comparisons = insertion_sort_count(temp, time);
            graphs_file << size << "," << type << ",Insertion," << comparisons << "," << time << "\n";
            cout << size << "," << type << ",Insertion," << comparisons << "," << time << "\n";
            comparisons = heap_sort_count(temp, time);
            graphs_file << size << "," << type << ",Heap," << comparisons << "," << time << "\n";
            cout << size << "," << type << ",Heap," << comparisons << "," << time << "\n";
        }
    }
}

int main() {
    test_comparisons();
    graphs_file.close();
    return 0;
}
