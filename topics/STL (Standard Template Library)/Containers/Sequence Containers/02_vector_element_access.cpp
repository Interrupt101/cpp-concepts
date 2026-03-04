#include <iostream>
#include <vector>

int main() {
    // Initialize a vector with some elements
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    // Access elements using the subscript operator []
    std::cout << "Element at index 0 using []: " << numbers[0] << std::endl; // No bound checking

    // Access elements using the at() method
    std::cout << "Element at index 1 using at(): " << numbers.at(1) << std::endl; // You can do  numbers.at(1) = 5

    // Access the first element using front()
    std::cout << "First element using front(): " << numbers.front() << std::endl;

    // Access the last element using back()
    std::cout << "Last element using back(): " << numbers.back() << std::endl;

    // Access the underlying array using data()
    int* dataPtr = numbers.data();
    std::cout << "First element using data(): " << *dataPtr << std::endl;
    
    // Display all elements using a range-based for loop
    std::cout << "All elements using range-based for loop: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
