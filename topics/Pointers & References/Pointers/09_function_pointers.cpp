#include <iostream>

int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

int main() {
    int (*operation)(int, int); // Function pointer

    operation = &add;
    std::cout << "Add: " << operation(10, 5) << std::endl;

    operation = &subtract;
    std::cout << "Subtract: " << operation(10, 5) << std::endl;

    return 0;
}
