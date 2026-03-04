/*
    Modifiers for a vector :
        clear, push_back, emplace_back ...
*/
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    // Display the initial state of the vector
    std::cout << "Initial vector: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // clear(): Removes all elements from the vector
    numbers.clear();
    std::cout << "After clear(): Size = " << numbers.size() << std::endl;

    // push_back(): Adds an element to the end
    numbers.push_back(10);
    numbers.push_back(20);
    std::cout << "After push_back(10) and push_back(20): ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // emplace_back(): Adds an element to the end (more efficient for complex types)
    numbers.emplace_back(30);
    std::cout << "After emplace_back(30): ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // insert(): Inserts elements at a specific position
    numbers.insert(numbers.begin() + 1, 15);
    std::cout << "After insert(15) at position 1: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // emplace(): Constructs elements in place at a specific position
    numbers.emplace(numbers.begin() + 2, 25);
    std::cout << "After emplace(25) at position 2: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // erase(): Removes elements at a specific position or range
    numbers.erase(numbers.begin() + 1);
    std::cout << "After erase element at position 1: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // pop_back(): Removes the last element
    numbers.pop_back();
    std::cout << "After pop_back(): ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // resize(): Resizes the container to contain count elements
    numbers.resize(5, 100);  // If new size is greater, new elements are initialized with 100
    std::cout << "After resize(5, 100): ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // swap(): Swaps the contents with another vector
    std::vector<int> otherNumbers = {1, 2, 3};
    numbers.swap(otherNumbers);
    std::cout << "After swap with another vector (1, 2, 3): ";
    std::cout << "numbers: ";
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    std::cout << " and otherNumbers: ";
    for (const auto& num : otherNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
