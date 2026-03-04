// This file demonstrates the usage of std::unordered_multiset in C++.
//
// Implementation Details:
// - std::unordered_multiset is implemented using a hash table.
// - It provides average-case O(1) time complexity for insertions, deletions, and lookups.
// - The elements are not stored in any specific order and multiple elements with the same value are allowed.
//
// Complexity:
// - Insertion: Average O(1), worst-case O(n) if many collisions occur
// - Deletion: Average O(1), worst-case O(n)
// - Search: Average O(1), worst-case O(n)
//
// Usage:
// - std::unordered_multiset is used for storing multiple elements with the same value and provides fast average-time complexity operations.

#include <iostream>
#include <unordered_set>
#include <string>

int main() {
    // Creating an unordered_multiset of strings
    std::unordered_multiset<std::string> myunorderedmultiset;

    // Inserting elements
    myunorderedmultiset.insert("apple");
    myunorderedmultiset.insert("banana");
    myunorderedmultiset.insert("cherry");
    myunorderedmultiset.insert("banana"); // Duplicate element
    myunorderedmultiset.insert("apple");  // Another duplicate element

    // Printing the unordered_multiset
    std::cout << "Unordered multiset elements:\n";
    for (const auto& elem : myunorderedmultiset) {
        std::cout << elem << '\n';
    }

    // Accessing elements with a specific value
    std::string key = "banana";
    auto range = myunorderedmultiset.equal_range(key);
    std::cout << "\nElements with value '" << key << "':\n";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << *it << '\n';
    }

    // Counting occurrences of a specific value
    std::cout << "\nNumber of occurrences of '" << key << "': " << myunorderedmultiset.count(key) << '\n';

    // Removing elements with a specific value
    myunorderedmultiset.erase("apple");
    std::cout << "\nAfter erasing 'apple':\n";
    for (const auto& elem : myunorderedmultiset) {
        std::cout << elem << '\n';
    }

    // Size of the unordered_multiset
    std::cout << "\nSize of the unordered multiset: " << myunorderedmultiset.size() << '\n';

    // Using iterators
    std::cout << "\nUnordered multiset elements using iterators:\n";
    for (std::unordered_multiset<std::string>::iterator it = myunorderedmultiset.begin(); it != myunorderedmultiset.end(); ++it) {
        std::cout << *it << '\n';
    }

    // Clearing the unordered_multiset
    myunorderedmultiset.clear();
    std::cout << "\nAfter clearing, size of the unordered multiset: " << myunorderedmultiset.size() << '\n';

    return 0;
}
