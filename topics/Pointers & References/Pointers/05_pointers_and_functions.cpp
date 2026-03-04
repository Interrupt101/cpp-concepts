#include <iostream>

void increment(int* p) {
    (*p)++;
}

int main() {
    int a = 10;
    increment(&a);

    std::cout << "Value of a after increment: " << a << std::endl;

    return 0;
}
