// pointers.cpp
// Understanding Pointers in C++

#include <iostream>
using namespace std;

void functionWithPointer(int* ptr) {
    cout << "Value at pointer: " << *ptr << endl; // Dereferencing the pointer
}

int main() {
    // Introduction to pointers
    int var = 42;                   // An integer variable
    int* ptr = &var;               // Pointer declaration and initialization
    cout << "Value of var: " << var << endl;
    cout << "Address of var: " << &var << endl;
    cout << "Value at ptr: " << *ptr << endl; // Dereferencing

    // Pointer arithmetic
    int arr[3] = {1, 2, 3};        // An array
    int* arrPtr = arr;            // Pointer to the first element of the array

    cout << "Array elements using pointer arithmetic:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << *(arrPtr + i) << " "; // Accessing array elements using pointer arithmetic
    }
    cout << endl;

    // Pointers and arrays
    cout << "Accessing array elements directly:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << arr[i] << " "; // Accessing array elements directly
    }
    cout << endl;

    // Pointers to functions
    void (*funcPtr)(int*) = functionWithPointer; // Pointer to a function
    funcPtr(ptr); // Calling the function using pointer to function

    // Pointers to pointers (double pointers)
    int** doublePtr = &ptr; // Pointer to a pointer
    cout << "Value at doublePtr: " << **doublePtr << endl; // Dereferencing twice

    // Null pointers and nullptr
    int* nullPtr = nullptr; // C++11 way to initialize a null pointer
    if (nullPtr == nullptr) {
        cout << "nullPtr is null." << endl;
    }

    // const pointers and pointer const
    int value = 100;
    const int* constPtr = &value; // Pointer to const int
    cout << "Value pointed by constPtr: " << *constPtr << endl;

    // const pointer
    int* const constPointer = &var; // const pointer
    *constPointer = 50; // Allowed: changing the value of var
    cout << "Updated var: " << var << endl;

    // const pointer (to const)
    const int* const constPointerToConst = &value; // const pointer to const
    // *constPointerToConst = 200; // Error: cannot change value through a const pointer to const

    return 0;
}
