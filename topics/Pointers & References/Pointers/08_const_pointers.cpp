#include <iostream>

int main() {
    int a = 10;
    int b = 20;

    const int* p1 = &a; // Pointer to constant (data is constant)
    int* const p2 = &a; // Constant pointer (pointer is constant)
    const int* const p3 = &a; // Constant pointer to constant

    // *p1 = 30; // Error: Cannot modify data through p1
    p1 = &b; // Okay: Can change the pointer

    *p2 = 30; // Okay: Can modify data
    // p2 = &b; // Error: Cannot change the pointer

    return 0;
}
