#include <iostream>

void printValue(const int& ref) {
    std::cout << "Value: " << ref << std::endl;
    // ref++; // Error: Cannot modify a const reference
}

int main() {
    int a = 10;
    printValue(a);

    return 0;
}
