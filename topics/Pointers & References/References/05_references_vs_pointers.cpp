#include <iostream>

int main() {
    int a = 10;
    int* p = &a; // Pointer
    int& ref = a; // Reference

    std::cout << "Pointer p points to: " << *p << std::endl;
    std::cout << "Reference ref refers to: " << ref << std::endl;

    p++; // Pointer can be incremented
    // ref++; // Error: Reference cannot be incremented

    return 0;
}
