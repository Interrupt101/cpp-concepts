#include <iostream>

void increment(int& ref) {
    ref++; // Modifies the original variable
}

int main() {
    int a = 10;
    increment(a);

    std::cout << "Value of a after increment : " << a << std::endl;

    return 0;
}
