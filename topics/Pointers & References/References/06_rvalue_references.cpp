#include <iostream>

void printValue(int&& ref) { // rvalue reference
    std::cout << "Rvalue reference: " << ref << std::endl;
}

int main() {
    int a = 10;
    printValue(10); // OK: 10 is an rvalue
    // printValue(a); // Error: a is an lvalue

    return 0;
}
