#include <iostream>
using namespace std;

class ArrayStack {
    int arr[100];
    int top;
public:
    ArrayStack() { top = -1; }
    void push(int val) { arr[++top] = val; }
    int pop() { return arr[top--]; }
    bool isEmpty() { return top == -1; }
    int size() { return top + 1; }
};

struct Node {
    int data;
    Node* next;
};

class LinkedStack {
    Node* top;
public:
    LinkedStack() { top = nullptr; }

    void push(int val) {
        Node* n = new Node();
        n->data = val;
        n->next = top;
        top = n;
    }

    int pop() {
        int val = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    bool isEmpty() { return top == nullptr; }

    void display() {
        Node* cur = top;
        cout << "Stack3 (top -> bottom): ";
        while (cur != nullptr) {
            cout << cur->data << " ";
            cur = cur->next;
        }
        cout << endl;
    }
};

class CircularQueue {
    int* arr;
    int capacity, front, rear, count;
public:
    CircularQueue(int cap) {
        capacity = cap;
        arr = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    bool isFull() { return count == capacity; }
    bool isEmpty() { return count == 0; }

    void enqueue(int val) {
        if (isFull()) {
            cout << "Queue is full\n";
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = val;
        count++;
    }

    void display() {
        cout << "Circular Queue (front -> rear): ";
        int idx = front;
        for (int i = 0; i < count; i++) {
            cout << arr[idx] << " ";
            idx = (idx + 1) % capacity;
        }
        cout << endl;
    }
};

void readStackInBottomToTopOrder(int* result, int n) {
    ArrayStack s;
    for (int i = 0; i < n; i++) {
        cin >> result[i];
        s.push(result[i]);
    }
}

int main() {
    int n1, n2;

    cout << "Enter size of Stack 1: ";
    cin >> n1;
    int stack1[100];
    cout << "Enter " << n1 << " elements of Stack 1 (bottom to top): ";
    readStackInBottomToTopOrder(stack1, n1);

    cout << "Enter size of Stack 2: ";
    cin >> n2;
    int stack2[100];
    cout << "Enter " << n2 << " elements of Stack 2 (bottom to top): ";
    readStackInBottomToTopOrder(stack2, n2);

    LinkedStack stack3;
    int i = 0, j = 0;
    while (i < n1 && j < n2) {
        stack3.push(stack1[i]);
        stack3.push(stack2[j]);
        i++;
        j++;
    }
    while (i < n1) {
        stack3.push(stack1[i]);
        i++;
    }
    while (j < n2) {
        stack3.push(stack2[j]);
        j++;
    }

    cout << "\n";
    stack3.display();

    int total = n1 + n2;
    int merged[200];
    for (int k = 0; k < total; k++) {
        merged[k] = stack3.pop();
    }

    for (int a = 0; a < total - 1; a++) {
        for (int b = 0; b < total - 1 - a; b++) {
            if (merged[b] > merged[b + 1]) {
                int t = merged[b];
                merged[b] = merged[b + 1];
                merged[b + 1] = t;
            }
        }
    }

    cout << "Sorted elements: ";
    for (int k = 0; k < total; k++) cout << merged[k] << " ";
    cout << endl << endl;

    CircularQueue cq(total);
    for (int k = 0; k < total; k++) {
        cq.enqueue(merged[k]);
    }
    cq.display();

    return 0;
}
