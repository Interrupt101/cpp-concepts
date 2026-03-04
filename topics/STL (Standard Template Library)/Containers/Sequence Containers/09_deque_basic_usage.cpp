#include <iostream>
#include <deque>

int main() {
    std::deque<int> dq = {1, 2, 3, 4, 5};

    // Access elements
    std::cout << "First element: " << dq.front() << std::endl;
    std::cout << "Last element: " << dq.back() << std::endl;

    // Iterate using range-based for loop
    std::cout << "Elements: ";
    for (const int& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Size of the deque
    std::cout << "Deque size: " << dq.size() << std::endl;

    return 0;
}
