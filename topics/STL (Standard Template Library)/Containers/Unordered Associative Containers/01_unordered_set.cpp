// This file demonstrates the usage of std::unordered_set in C++.
//
// Implementation Details:
// - std::unordered_set is implemented using a hash table.
// - It provides average-case O(1) time complexity for insertions, deletions, and lookups.
// - The elements are not stored in any specific order.
//
// Complexity:
// - Insertion: Average O(1), worst-case O(n) if many collisions occur
// - Deletion: Average O(1), worst-case O(n)
// - Search: Average O(1), worst-case O(n)
//
// Usage:
// - std::unordered_set is used for storing unique elements with fast average-time complexity operations.

#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    // Creating an unordered_set of strings
    std::unordered_set<std::string> myunorderedset;

    // Inserting elements
    myunorderedset.insert("apple");
    myunorderedset.insert("banana");
    myunorderedset.insert("cherry");

    // Printing the unordered_set
    std::cout << "Unordered set elements:\n";
    for (const auto& elem : myunorderedset) {
        std::cout << elem << '\n';
    }

    // Checking if an element exists
    std::string key = "banana";
    if (myunorderedset.find(key) != myunorderedset.end()) {
        std::cout << key << " exists in the unordered set.\n";
    } else {
        std::cout << key << " does not exist in the unordered set.\n";
    }

    // Removing elements
    myunorderedset.erase("apple");
    std::cout << "\nAfter erasing 'apple':\n";
    for (const auto& elem : myunorderedset) {
        std::cout << elem << '\n';
    }

    // Size of the unordered_set
    std::cout << "\nSize of the unordered set: " << myunorderedset.size() << '\n';

    // Using iterators
    std::cout << "\nUnordered set elements using iterators:\n";
    for (std::unordered_set<std::string>::iterator it = myunorderedset.begin(); it != myunorderedset.end(); ++it) {
        std::cout << *it << '\n';
    }

    // Clearing the unordered_set
    myunorderedset.clear();
    std::cout << "\nAfter clearing, size of the unordered set: " << myunorderedset.size() << '\n';

    return 0;
}
