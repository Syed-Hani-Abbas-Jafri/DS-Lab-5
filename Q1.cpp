#include <iostream>
using namespace std;

class Stack {
    int arr[100];
    int top;
public:
    Stack() { top = -1; }

    void push(int val) {
        if (top == 99) {
            cout << "Stack Overflow\n";
            return;
        }
        arr[++top] = val;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack Underflow\n";
            return -1;
        }
        return arr[top--];
    }

    bool isEmpty() { return top == -1; }

    int size() { return top + 1; }
};

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    Stack s;
    cout << "Enter " << n << " elements (first element = bottom, last element = top):\n";
    for (int i = 0; i < n; i++) {
        int val;
        cin >> val;
        s.push(val);
    }

    int sz = s.size();
    int temp[100];

    for (int i = sz - 1; i >= 0; i--) {
        temp[i] = s.pop();
    }

    int maxVal = temp[0], minVal = temp[0];
    for (int i = 0; i < sz; i++) {
        if (temp[i] > maxVal) maxVal = temp[i];
        if (temp[i] < minVal) minVal = temp[i];
    }

    cout << "\nMaximum value: " << maxVal << endl;
    cout << "Minimum value: " << minVal << endl;

    if (sz % 2 != 0) {
        cout << "Middle element: " << temp[sz / 2] << endl;
    } else {
        cout << "Middle elements: " << temp[sz / 2 - 1] << " and " << temp[sz / 2] << endl;
    }

    for (int i = 0; i < sz; i++) {
        s.push(temp[i]);
    }

    return 0;
}
