#include <iostream>
#include <forward_list>

int main() {
    // Declare and initialize a forward list
    std::forward_list<int> fwd_list = {1, 2, 3, 4, 5};
    // Insert elements at the beginning
    fwd_list.push_front(0);
    // Insert elements after a specific element
    auto it = fwd_list.begin();
    ++it; // Move iterator to the second position
    fwd_list.insert_after(it, 6);

    // Delete elements
    fwd_list.pop_front(); // Removes the first element
    it = fwd_list.begin();
    ++it; // Move iterator to the second position
    fwd_list.erase_after(it); // Removes the third element

    // Iterate using iterator
    std::cout << "Elements using iterator: ";
    for (auto it = fwd_list.begin(); it != fwd_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
