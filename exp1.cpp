#include <iostream>
using namespace std;

// Define the maximum size of the stack
const int MAX_SIZE = 100;

// Define the stack class
class Stack {
private:
    int arr[MAX_SIZE];
    int top;

public:
    // Constructor
    Stack() {
        top = -1; // Initialize top to -1 to indicate an empty stack
    }

    // Function to push an element onto the stack
    void push(int value) {
        if (top == MAX_SIZE - 1) {
            cout << "Stack Overflow: Cannot push element, stack is full." << endl;
        } else {
            arr[++top] = value;
            cout << "Pushed " << value << " onto the stack." << endl;
        }
    }

    // Function to pop an element from the stack
    void pop() {
        if (top == -1) {
            cout << "Stack Underflow: Cannot pop element, stack is empty." << endl;
        } else {
            cout << "Popped " << arr[top--] << " from the stack." << endl;
        }
    }

    // Function to display the elements in the stack
    void display() {
        if (top == -1) {
            cout << "Stack is empty." << endl;
        } else {
            cout << "Elements in the stack: ";
            for (int i = 0; i <= top; ++i) {
                cout << arr[i] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Stack stack; // Create a stack object

    int choice, element;

    do {
        cout << "Choose operation:\n1. Push\n2. Pop\n3. Display\n4. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter element to push onto the stack: ";
                cin >> element;
                stack.push(element);
                break;
            case 2:
                stack.pop();
                break;
            case 3:
                stack.display();
                break;
            case 4:
                cout << "Exiting the program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
