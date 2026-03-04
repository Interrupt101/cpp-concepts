// This file demonstrates the usage of std::priority_queue in C++.
//
// Implementation Details:
// - std::priority_queue is a container adapter that provides priority-based access to elements.
// - It is typically implemented using a heap, which is usually a binary heap.
//
// Complexity:
// - Push: O(log n)
// - Pop: O(log n)
// - Top: O(1)
// - Size: O(1)
//
// Usage:
// - std::priority_queue is used to manage a collection of elements where the highest priority element is accessed first.


#include <iostream>
#include <queue>
#include <vector>

int main() {
    // Creating a priority_queue of integers
    std::priority_queue<int> mypriorityqueue;

    // Pushing elements
    mypriorityqueue.push(10);
    mypriorityqueue.push(5);
    mypriorityqueue.push(20);

    // Printing the top element
    std::cout << "Top element: " << mypriorityqueue.top() << '\n';

    // Popping elements
    mypriorityqueue.pop();
    std::cout << "Top element after pop: " << mypriorityqueue.top() << '\n';

    // Size of the priority_queue
    std::cout << "Size of the priority_queue: " << mypriorityqueue.size() << '\n';

    // Checking if the priority_queue is empty
    std::cout << "Is the priority_queue empty? " << (mypriorityqueue.empty() ? "Yes" : "No") << '\n';

    // Clearing the priority_queue
    while (!mypriorityqueue.empty()) {
        mypriorityqueue.pop();
    }
    std::cout << "Size of the priority_queue after clearing: " << mypriorityqueue.size() << '\n';

    return 0;
}
