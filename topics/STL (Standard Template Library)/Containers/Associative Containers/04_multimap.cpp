// This file demonstrates the usage of std::multimap in C++.
//
// Implementation Details:
// - std::multimap is typically implemented using a self-balancing binary search tree, such as a Red-Black Tree.
// - This ensures that all operations such as insertions, deletions, and lookups are performed in O(log n) time on average.
//
// Complexity:
// - Insertion: O(log n)
// - Deletion: O(log n)
// - Search: O(log n)
//
// Usage:
// - std::multimap is used for associative arrays where keys are not unique and elements are stored in a sorted order based on the key.
// - It provides fast lookups, insertions, and deletions while maintaining order, and allows multiple elements with the same key.

#include <iostream>
#include <map>
#include <string>

int main() {
    // Creating a multimap of string to int
    std::multimap<std::string, int> mymultimap;

    // Inserting elements
    mymultimap.insert(std::make_pair("apple", 1));
    mymultimap.insert(std::make_pair("banana", 2));
    mymultimap.insert(std::make_pair("cherry", 3));
    mymultimap.insert(std::make_pair("banana", 4)); // Duplicate key
    mymultimap.insert(std::make_pair("apple", 5));  // Another duplicate key

    // Printing the multimap
    std::cout << "Multimap elements:\n";
    for (const auto& elem : mymultimap) {
        std::cout << elem.first << ": " << elem.second << '\n';
    }

    // Accessing elements with a specific key
    std::string key = "banana";
    auto range = mymultimap.equal_range(key);
    std::cout << "\nElements with key '" << key << "':\n";
    for (auto it = range.first; it != range.second; ++it) {
        std::cout << it->first << ": " << it->second << '\n';
    }

    // Counting occurrences of a specific key
    std::cout << "\nNumber of occurrences of '" << key << "': " << mymultimap.count(key) << '\n';

    // Removing elements with a specific key
    mymultimap.erase("apple");
    std::cout << "\nAfter erasing 'apple':\n";
    for (const auto& elem : mymultimap) {
        std::cout << elem.first << ": " << elem.second << '\n';
    }

    // Size of the multimap
    std::cout << "\nSize of the multimap: " << mymultimap.size() << '\n';

    // Using iterators
    std::cout << "\nMultimap elements using iterators:\n";
    for (std::multimap<std::string, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it) {
        std::cout << it->first << ": " << it->second << '\n';
    }

    // Clearing the multimap
    mymultimap.clear();
    std::cout << "\nAfter clearing, size of the multimap: " << mymultimap.size() << '\n';

    return 0;
}
