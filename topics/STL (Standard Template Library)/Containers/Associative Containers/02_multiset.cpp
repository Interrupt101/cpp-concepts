/*
- Implementation Details
    1. Underlying Data Structure:
        std::multiset is typically implemented using a 
        self-balancing binary search tree, such as a Red-Black Tree. 
        This provides efficient insertions, deletions, and lookups while maintaining order.

    2. Properties:
        - Ordered: Elements are stored in a sorted manner according to the comparator 
                (by default, std::less<T>).
        - Multiple Elements: Allows multiple elements with the same value.

    3. Performance Characteristics:
        - Insertions/Deletions: Average time complexity is O(log n).
        - Search: Average time complexity is O(log n).

*/
#include <iostream>
#include <set>

int main() {
    // Creating a multiset of integers
    std::multiset<int> mymultiset;

    // Inserting elements
    mymultiset.insert(10);
    mymultiset.insert(20);
    mymultiset.insert(30);
    mymultiset.insert(20); // Duplicate elements are allowed
    mymultiset.insert(10); // Another duplicate

    // Printing the multiset
    std::cout << "Multiset elements: ";
    for (const int& elem : mymultiset) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    // Counting the number of occurrences of an element
    int value = 20;
    std::cout << "Number of occurrences of " << value << ": " << mymultiset.count(value) << std::endl;

    // Finding elements
    auto it = mymultiset.find(20);
    if (it != mymultiset.end()) {
        std::cout << "Element 20 found in the multiset." << std::endl;
    } else {
        std::cout << "Element 20 not found in the multiset." << std::endl;
    }

    // Removing elements
    mymultiset.erase(20); // Removes all occurrences of 20
    std::cout << "After erasing 20: ";
    for (const int& elem : mymultiset) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;

    // Size of the multiset
    std::cout << "Size of the multiset: " << mymultiset.size() << std::endl;

    // Using iterators
    std::cout << "Multiset elements using iterators: ";
    for (std::multiset<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Clearing the multiset
    mymultiset.clear();
    std::cout << "After clearing, size of the multiset: " << mymultiset.size() << std::endl;

    // Demonstrating a multiset of strings
    std::multiset<std::string> strmultiset = {"apple", "banana", "apple", "cherry"};
    std::cout << "String multiset elements: ";
    for (const auto& str : strmultiset) {
        std::cout << str << ' ';
    }
    std::cout << std::endl;

    return 0;
}
