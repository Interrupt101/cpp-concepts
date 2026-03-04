#include <iostream>

int main() {
    int a = 10;
    void* p = &a; // Void pointer

    std::cout << "Address stored in p: " << p << std::endl;

    // Dereferencing a void pointer requires casting
    std::cout << "Value of a through void pointer: " << *(static_cast<int*>(p)) << std::endl;

    return 0;
}
