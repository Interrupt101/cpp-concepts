#include <iostream>
#include <set>

int main() {
    // Creating a set of integers
    std::set<int> myset;

    // Inserting elements
    myset.insert(10);
    myset.insert(20);
    myset.insert(30);
    myset.insert(20); // Duplicate elements are not added

    // Printing the set
    std::cout << "Set elements: ";
    for (const int& elem : myset) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    // Checking if an element is in the set
    int value = 20;
    if (myset.find(value) != myset.end()) {
        std::cout << value << " is in the set." << std::endl;
    } else {
        std::cout << value << " is not in the set." << std::endl;
    }

    // Removing elements
    myset.erase(20);
    std::cout << "After erasing 20: ";
    for (const int& elem : myset) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    // Size of the set
    std::cout << "Size of the set: " << myset.size() << std::endl;

    // Using iterators
    std::cout << "Set elements using iterators: ";
    for (std::set<int>::iterator it = myset.begin(); it != myset.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Clearing the set
    myset.clear();
    std::cout << "After clearing, size of the set: " << myset.size() << std::endl;

    // Demonstrating a set of strings
    std::set<std::string> strset = {"apple", "banana", "cherry"};
    std::cout << "String set elements: ";
    for (const auto& str : strset) {
        std::cout << str << ' ';
    }
    std::cout << std::endl;

    return 0;
}
