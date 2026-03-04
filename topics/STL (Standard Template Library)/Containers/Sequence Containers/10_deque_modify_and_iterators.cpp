#include <iostream>
#include <deque>

int main() {
    // Declare and initialize a deque
    std::deque<int> dq = {1, 2, 3, 4, 5};

    // Modify elements
    dq[0] = 10;
    dq.at(1) = 20;

    // Insert and delete elements at both ends
    dq.push_front(0);
    dq.push_back(6);
    dq.pop_front();
    dq.pop_back();

    // Iterate using iterators
    std::cout << "Elements using iterators: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Reverse iteration
    std::cout << "Elements in reverse order: ";
    for (auto rit = dq.rbegin(); rit != dq.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    return 0;
}
