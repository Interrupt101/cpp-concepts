#include <iostream>
#include <list>

int main() {
    std::list<int> mylist = {10, 20, 30, 40, 50};

    auto it = mylist.begin();
    std::advance(it, 2); // Move iterator to the 3rd position
    mylist.insert(it, 25); // Insert 25 before the 3rd element

    std::cout << "After insertion: ";
    for (int n : mylist) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    // Erasing elements
    it = mylist.begin();
    std::advance(it, 1); // Move iterator to the 2nd position
    mylist.erase(it); // Erase the 2nd element

    std::cout << "After erasing: ";
    for (int n : mylist) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    // Modifying elements
    for (int& n : mylist) {
        n *= 2; // Double each element
    }

    std::cout << "After modifying: ";
    for (int n : mylist) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    return 0;
}
