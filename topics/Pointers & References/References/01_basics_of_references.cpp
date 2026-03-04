#include <iostream>

int main() {
    int a = 10;
    int& ref = a; // ref is a reference to a

    std::cout << "Value of a: " << a << std::endl;
    std::cout << "Value of ref: " << ref << std::endl;

    ref = 20; // Modifies a
    std::cout << "Value of a after modifying ref: " << a << std::endl;

    return 0;
}
