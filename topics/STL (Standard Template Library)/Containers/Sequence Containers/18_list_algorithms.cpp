#include <iostream>
#include <list>
#include <algorithm>

int main() {
    std::list<int> mylist = {10, 20, 30, 40, 50};

    // Using iterators to traverse the list
    std::cout << "Traversing the list: ";
    for (auto it = mylist.begin(); it != mylist.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << std::endl;

    // Using reverse iterators to traverse the list backwards
    std::cout << "Traversing the list backwards: ";
    for (auto rit = mylist.rbegin(); rit != mylist.rend(); ++rit) {
        std::cout << *rit << ' ';
    }
    std::cout << std::endl;

    // Using standard algorithms
    // Find an element
    auto it = std::find(mylist.begin(), mylist.end(), 30);
    if (it != mylist.end()) {
        std::cout << "Element 30 found in the list." << std::endl;
    } else {
        std::cout << "Element 30 not found in the list." << std::endl;
    }

    // Sort the list
    mylist.sort();
    std::cout << "List after sorting: ";
    for (int n : mylist) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    // Remove duplicates
    mylist.unique();
    std::cout << "List after removing duplicates: ";
    for (int n : mylist) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    return 0;
}
