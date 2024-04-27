#include <iostream>

using namespace std;

// linked list node
struct ListNode {
    int data;
    ListNode* previous;
    ListNode* next;

    ListNode(int value) : data(value), previous(nullptr), next(nullptr) {}
};

class SortedDoublyList {
    ListNode* front;
    ListNode* rear;

public:
    SortedDoublyList() : front(nullptr), rear(nullptr) {}

    void addNode(int value) {
        ListNode* newNode = new ListNode(value);
        if (rear == nullptr) { // List is empty
            front = rear = newNode;
        } else {
            rear->next = newNode;
            newNode->previous = rear;
            rear = newNode;
        }
    }

    void showList() {
        ListNode* current = front;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    ListNode* getFront() {
        return front;
    }

    ListNode* getRear() {
        return rear;
    }
};

// Helper function to swap the data of two list nodes
void swapValues(ListNode* node1, ListNode* node2) {
    int temporary = node1->data;
    node1->data = node2->data;
    node2->data = temporary;
}

//  partition the linked list
ListNode* partitionList(ListNode* start, ListNode* end) {
    int pivot = end->data;
    ListNode* i = start->previous;

    for (ListNode* j = start; j != end; j = j->next) {
        if (j->data <= pivot) {
            i = (i == nullptr) ? start : i->next;
            swapValues(i, j);
        }
    }
    i = (i == nullptr) ? start : i->next;
    swapValues(i, end);
    return i;
}

// implement QuickSort on the linked list
void quickSortList(ListNode* start, ListNode* end) {
    if (end != nullptr && start != end && start != end->next) {
        ListNode* p = partitionList(start, end);
        quickSortList(start, p->previous);
        quickSortList(p->next, end);
    }
}


int main() {
    SortedDoublyList bosaty;
    bosaty.addNode(9);
    bosaty.addNode(7);
    bosaty.addNode(8);
    bosaty.addNode(5);
    bosaty.addNode(6);

    cout << "Original list: ";
    bosaty.showList();
    quickSortList(bosaty.getFront(), bosaty.getRear());

    cout << "Sorted list: ";
    bosaty.showList();

    return 0;
}
