#include <iostream>

int main() {
    int a = 10;
    int* p = &a;
    int** pp = &p; // Pointer to pointer

    std::cout << "Value of a: " << a << std::endl;
    std::cout << "Value of p: " << *p << std::endl;
    std::cout << "Value of pp: " << **pp << std::endl;

    return 0;
}
