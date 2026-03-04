#include <iostream>
#include <forward_list>
#include <algorithm>
#include <vector>

int main() {
    // Declaration
    std::forward_list<int> fwd_list = {5, 3, 1, 4, 2};

    // Sort the forward list (requires a temporary std::vector)
    std::vector<int> temp(fwd_list.begin(), fwd_list.end());
    std::sort(temp.begin(), temp.end());
    std::copy(temp.begin(), temp.end(), fwd_list.begin());

    // Print sorted elements
    std::cout << "Sorted elements: ";
    for (const int& elem : fwd_list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Find an element
    auto it = std::find(fwd_list.begin(), fwd_list.end(), 3);
    if (it != fwd_list.end()) {
        std::cout << "Element 3 found" << std::endl;
    } else {
        std::cout << "Element 3 not found" << std::endl;
    }

    // Check if all elements satisfy a condition
    bool all_positive = std::all_of(fwd_list.begin(), fwd_list.end(), [](int x) { return x > 0; });
    std::cout << "All elements are positive: " << (all_positive ? "true" : "false") << std::endl;

    return 0;
}
