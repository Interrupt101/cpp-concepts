/// Forward list basics : Signly linked list

#include <iostream>
#include <forward_list>

int main() {
    // Declare and initialize a forward list
    std::forward_list<int> fwd_list = {1, 2, 3, 4, 5};
    // Access and iterate elements
    std::cout << "Elements: ";
    for (const int& elem : fwd_list) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
    // Size of the forward list
    std::cout << "Forward list size: " << std::distance(fwd_list.begin(), fwd_list.end()) << std::endl;
    return 0;
}
