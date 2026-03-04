#include <iostream>
#include <deque>
#include <algorithm>

int main() {
    // Declaration
    std::deque<int> dq = {5, 3, 1, 4, 2};

    // Sorting
    std::sort(dq.begin(), dq.end());

    // Print sorted elements
    std::cout << "Sorted elements: ";
    for (const int& elem : dq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Find an element
    auto it = std::find(dq.begin(), dq.end(), 3);
    if (it != dq.end()) {
        std::cout << "Element 3 found at position: " << std::distance(dq.begin(), it) << std::endl;
    } else {
        std::cout << "Element 3 not found" << std::endl;
    }

    // Check if all elements satisfy a condition
    bool all_positive = std::all_of(dq.begin(), dq.end(), [](int x) { return x > 0; });
    std::cout << "All elements are positive: " << (all_positive ? "true" : "false") << std::endl;

    return 0;
}
