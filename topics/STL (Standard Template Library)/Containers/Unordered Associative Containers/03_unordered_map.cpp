// This file demonstrates the usage of std::unordered_map in C++.
//
// Implementation Details:
// - std::unordered_map is implemented using a hash table.
// - It provides average-case O(1) time complexity for insertions, deletions, and lookups.
// - The keys are not stored in any specific order.
//
// Complexity:
// - Insertion: Average O(1), worst-case O(n) if many collisions occur
// - Deletion: Average O(1), worst-case O(n)
// - Search: Average O(1), worst-case O(n)
//
// Usage:
// - std::unordered_map is used for associative arrays where keys are unique and elements are accessed via hash-based indexing.
// - It provides fast average-time complexity operations and does not maintain any order among the keys.

#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // Creating an unordered_map of string to int
    std::unordered_map<std::string, int> myunorderedmap;

    // Inserting elements
    myunorderedmap["apple"] = 1;
    myunorderedmap["banana"] = 2;
    myunorderedmap["cherry"] = 3;

    // Inserting elements using insert function
    myunorderedmap.insert(std::make_pair("date", 4));
    myunorderedmap.insert({"elderberry", 5});

    // Printing the unordered_map
    std::cout << "Unordered map elements:\n";
    for (const auto& elem : myunorderedmap) {
        std::cout << elem.first << ": " << elem.second << '\n';
    }

    // Accessing elements
    std::cout << "\nValue for key 'banana': " << myunorderedmap["banana"] << '\n';

    // Modifying elements
    myunorderedmap["banana"] = 20;
    std::cout << "Modified value for key 'banana': " << myunorderedmap["banana"] << '\n';

    // Checking if a key exists
    std::string key = "cherry";
    if (myunorderedmap.find(key) != myunorderedmap.end()) {
        std::cout << key << " exists in the unordered map.\n";
    } else {
        std::cout << key << " does not exist in the unordered map.\n";
    }

    // Removing elements
    myunorderedmap.erase("apple");
    std::cout << "\nAfter erasing 'apple':\n";
    for (const auto& elem : myunorderedmap) {
        std::cout << elem.first << ": " << elem.second << '\n';
    }

    // Size of the unordered_map
    std::cout << "\nSize of the unordered map: " << myunorderedmap.size() << '\n';

    // Using iterators
    std::cout << "\nUnordered map elements using iterators:\n";
    for (std::unordered_map<std::string, int>::iterator it = myunorderedmap.begin(); it != myunorderedmap.end(); ++it) {
        std::cout << it->first << ": " << it->second << '\n';
    }

    // Clearing the unordered_map
    myunorderedmap.clear();
    std::cout << "\nAfter clearing, size of the unordered map: " << myunorderedmap.size() << '\n';

    return 0;
}
