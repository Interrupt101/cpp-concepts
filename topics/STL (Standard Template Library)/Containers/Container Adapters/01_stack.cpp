// This file demonstrates the usage of std::stack in C++.
//
// Implementation Details:
// - std::stack is a container adapter that provides LIFO (Last-In-First-Out) functionality.
// - It is implemented using other underlying containers, typically std::deque or std::vector.
//
// Complexity:
// - Push: O(1)
// - Pop: O(1)
// - Top: O(1)
// - Size: O(1)
//
// Usage:
// - std::stack is used to manage a collection of elements where the last element added is the first to be removed.

#include <iostream>
#include <stack>

int main() {
    // Creating a stack of integers
    std::stack<int> mystack;

    // Pushing elements
    mystack.push(1);
    mystack.push(2);
    mystack.push(3);

    // Printing the top element
    std::cout << "Top element: " << mystack.top() << '\n';

    // Popping elements
    mystack.pop();
    std::cout << "Top element after pop: " << mystack.top() << '\n';

    // Size of the stack
    std::cout << "Size of the stack: " << mystack.size() << '\n';

    // Checking if the stack is empty
    std::cout << "Is the stack empty? " << (mystack.empty() ? "Yes" : "No") << '\n';

    // Clearing the stack
    while (!mystack.empty()) {
        mystack.pop();
    }
    std::cout << "Size of the stack after clearing: " << mystack.size() << '\n';

    return 0;
}
