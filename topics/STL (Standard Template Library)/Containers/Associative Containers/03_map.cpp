// This file demonstrates the usage of std::map in C++.
// 
// Implementation Details:
// - std::map is typically implemented using a self-balancing binary search tree, 
//    such as a Red-Black Tree.
// - This ensures that all operations such as insertions, deletions, 
//    and lookups are performed in O(log n) time on average.
// 
// Complexity:
// - Insertion: O(log n)
// - Deletion: O(log n)
// - Search: O(log n)
// 
// Usage:
// - std::map is used for associative arrays where keys are unique and elements are stored in a sorted order based on the key.
// - It provides fast lookups, insertions, and deletions while maintaining order.

#include <iostream>
#include <map>
#include <string>

int main() {
    // Creating a map of string to int
    std::map<std::string, int> mymap;

    // Inserting elements
    mymap["apple"] = 1;
    mymap["banana"] = 2;
    mymap["cherry"] = 3;

    // Inserting elements using insert function
    mymap.insert(std::make_pair("date", 4));
    mymap.insert({"elderberry", 5});

    // Printing the map
    std::cout << "Map elements:\n";
    for (const auto& elem : mymap) {
        std::cout << elem.first << ": " << elem.second << '\n';
    }

    // Accessing elements
    std::cout << "\nValue for key 'banana': " << mymap["banana"] << '\n';

    // Modifying elements
    mymap["banana"] = 20;
    std::cout << "Modified value for key 'banana': " << mymap["banana"] << '\n';

    // Checking if a key exists
    std::string key = "cherry";
    if (mymap.find(key) != mymap.end()) {
        std::cout << key << " exists in the map.\n";
    } else {
        std::cout << key << " does not exist in the map.\n";
    }

    // Removing elements
    mymap.erase("apple");
    std::cout << "\nAfter erasing 'apple':\n";
    for (const auto& elem : mymap) {
        std::cout << elem.first << ": " << elem.second << '\n';
    }

    // Size of the map
    std::cout << "\nSize of the map: " << mymap.size() << '\n';

    // Using iterators
    std::cout << "\nMap elements using iterators:\n";
    for (std::map<std::string, int>::iterator it = mymap.begin(); it != mymap.end(); ++it) {
        std::cout << it->first << ": " << it->second << '\n';
    }

    // Clearing the map
    mymap.clear();
    std::cout << "\nAfter clearing, size of the map: " << mymap.size() << '\n';

    return 0;
}
