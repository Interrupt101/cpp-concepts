#include <iostream>
#include <array>

int main() {
    // Declare an array of 5 integers
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    // Access elements
    std::cout << "First element: " << arr[0] << std::endl;
    std::cout << "Second element: " << arr.at(1) << std::endl;  // Bounds-checked access

    // Iterate using range-based for loop
    std::cout << "Elements: ";
    for (const int& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Size of the array
    std::cout << "Array size: " << arr.size() << std::endl;

    return 0;
}
