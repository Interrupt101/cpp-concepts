#include <iostream>
#include <array>

int main() {
    // Declare and initialize an array
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    // Modify elements
    arr[0] = 10;
    arr.at(1) = 20;

    // Iterate using iterators
    std::cout << "Elements using iterators: ";
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Reverse iteration
    std::cout << "Elements in reverse order: ";
    for (auto rit = arr.rbegin(); rit != arr.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    return 0;
}
