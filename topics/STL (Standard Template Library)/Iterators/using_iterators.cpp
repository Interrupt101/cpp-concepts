#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>

int main() {
    // Example 1: Using Iterators with std::vector
    std::cout << "=== Using Iterators with std::vector ===" << std::endl;
    std::vector<int> vec = {10, 20, 30, 40, 50};

    // Using forward iterators to traverse and print the vector
    std::cout << "Vector elements: ";
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Using reverse iterators to traverse and print the vector in reverse
    std::cout << "Vector elements in reverse: ";
    for (std::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // Example 2: Using Iterators with std::list
    std::cout << "\n=== Using Iterators with std::list ===" << std::endl;
    std::list<int> lst = {1, 2, 3, 4, 5};

    // Using bidirectional iterators to traverse and print the list
    std::cout << "List elements: ";
    for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Example 3: Using Iterators with std::set
    std::cout << "\n=== Using Iterators with std::set ===" << std::endl;
    std::set<int> st = {5, 3, 8, 1, 4};

    // Using bidirectional iterators to traverse and print the set
    std::cout << "Set elements: ";
    for (std::set<int>::iterator it = st.begin(); it != st.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Example 4: Using Iterators with std::map
    std::cout << "\n=== Using Iterators with std::map ===" << std::endl;
    std::map<int, std::string> mp = {{1, "one"}, {2, "two"}, {3, "three"}};

    // Using bidirectional iterators to traverse and print the map
    std::cout << "Map elements: ";
    for (std::map<int, std::string>::iterator it = mp.begin(); it != mp.end(); ++it) {
        std::cout << "[" << it->first << ": " << it->second << "] ";
    }
    std::cout << std::endl;

    // Using constant iterators for read-only access to map elements
    std::cout << "Map elements using const iterator: ";
    for (std::map<int, std::string>::const_iterator it = mp.cbegin(); it != mp.cend(); ++it) {
        std::cout << "[" << it->first << ": " << it->second << "] ";
    }
    std::cout << std::endl;

    return 0;
}
