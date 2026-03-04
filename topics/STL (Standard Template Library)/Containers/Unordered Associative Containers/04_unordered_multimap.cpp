// This file demonstrates the usage of std::unordered_multimap in C++.
//
// Implementation Details:
// - std::unordered_multimap is implemented using a hash table.
// - It provides average-case O(1) time complexity for insertions, deletions, and lookups.
// - The keys are not stored in any specific order and multiple elements with the same key are allowed.
//
// Complexity:
// - Insertion: Average O(1), worst-case O(n) if many collisions occur
// - Deletion: Average O(1), worst-case O(n)
// - Search: Average O(1), worst-case O(n)
//
// Usage:
// - std::unordered_multimap is used for associative arrays where keys are not unique and elements are accessed via hash-based indexing.
// - It provides fast average-time complexity operations and allows multiple elements with the same key.

#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // Creating an unordered_multimap of string to int
    std::unordered_multimap<std::string, int> myunorderedmultimap;

    // Inserting elements
    myunorderedmultimap.insert(std::make_pair("apple", 1));
    myunorderedmultimap.insert(std::make_pair("banana", 2));
    myunorderedmultimap.insert(std::make_pair("cherry", 3));
    myunorderedmultimap.insert(std::make_pair("banana", 4)); // Duplicate key
    myunorderedmultimap.insert(std::make_pair("apple", 5));  // Another duplicate key

    // Printing the unordered_multimap
    std::cout << "Unordered multimap elements:\n";
    for (const auto& elem : myunorderedmultimap) {
        std::cout << elem.first << ": " << elem.second << '\n';
    }

    // Accessing elements with a specific key
    std::string key = "banana";
    auto range = myunorderedmultimap.equal_range(key);
    std::cout << "\nElements with key '" << key << "':\n";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ": " << it->second << '\n';
    }

    // Counting occurrences of a specific key
    std::cout << "\nNumber of occurrences of '" << key << "': " << myunorderedmultimap.count(key) << '\n';

    // Removing elements with a specific key
    myunorderedmultimap.erase("apple");
    std::cout << "\nAfter erasing 'apple':\n";
    for (const auto& elem : myunorderedmultimap) {
        std::cout << elem.first << ": " << elem.second << '\n';
    }

    // Size of the unordered_multimap
    std::cout << "\nSize of the unordered multimap: " << myunorderedmultimap.size() << '\n';

    // Using iterators
    std::cout << "\nUnordered multimap elements using iterators:\n";
    for (std::unordered_multimap<std::string, int>::iterator it = myunorderedmultimap.begin(); it != myunorderedmultimap.end(); ++it) {
        std::cout << it->first << ": " << it->second << '\n';
    }

    // Clearing the unordered_multimap
    myunorderedmultimap.clear();
    std::cout << "\nAfter clearing, size of the unordered multimap: " << myunorderedmultimap.size() << '\n';

    return 0;
}
