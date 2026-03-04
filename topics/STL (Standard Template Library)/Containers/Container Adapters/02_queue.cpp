// This file demonstrates the usage of std::queue in C++.
//
// Implementation Details:
// - std::queue is a container adapter that provides FIFO (First-In-First-Out) functionality.
// - It is implemented using other underlying containers, typically std::deque or std::list.
//
// Complexity:
// - Push: O(1)
// - Pop: O(1)
// - Front: O(1)
// - Back: O(1)
// - Size: O(1)
//
// Usage:
// - std::queue is used to manage a collection of elements where the first element added is the first to be removed.

#include <iostream>
#include <queue>

int main() {
    // Creating a queue of integers
    std::queue<int> myqueue;

    // Pushing elements
    myqueue.push(1);
    myqueue.push(2);
    myqueue.push(3);

    // Printing the front element
    std::cout << "Front element: " << myqueue.front() << '\n';

    // Printing the back element
    std::cout << "Back element: " << myqueue.back() << '\n';

    // Popping elements
    myqueue.pop();
    std::cout << "Front element after pop: " << myqueue.front() << '\n';

    // Size of the queue
    std::cout << "Size of the queue: " << myqueue.size() << '\n';

    // Checking if the queue is empty
    std::cout << "Is the queue empty? " << (myqueue.empty() ? "Yes" : "No") << '\n';

    // Clearing the queue
    while (!myqueue.empty()) {
        myqueue.pop();
    }
    std::cout << "Size of the queue after clearing: " << myqueue.size() << '\n';

    return 0;
}
