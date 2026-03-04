#include <iostream>
#include <array>

// Function to print elements of an array
void printArray(const std::array<int, 5>& arr) {
    for (const int& elem : arr) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main() {
    // Declare and initialize an array
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    // Pass array to a function
    std::cout << "Array elements: ";
    printArray(arr);

    return 0;
}
