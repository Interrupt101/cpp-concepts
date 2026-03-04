// dynamic_memory_allocation.cpp
// Dynamic Memory Allocation in C++

#include <iostream>
#include <memory> // For smart pointers
using namespace std;

int main() {
    // Dynamic memory allocation using new and delete
    int* ptr = new int;         // Allocate memory for an integer
    *ptr = 42;                  // Assign value
    cout << "Value allocated dynamically: " << *ptr << endl;
    delete ptr;                 // Free the allocated memory

    // Dynamic arrays
    int size;
    cout << "Enter size of the array: ";
    cin >> size;
    
    int* dynamicArray = new int[size]; // Allocate dynamic array
    for (int i = 0; i < size; i++) {
        dynamicArray[i] = i + 1;        // Assign values
    }
    
    cout << "Dynamic array elements: ";
    for (int i = 0; i < size; i++) {
        cout << dynamicArray[i] << " "; // Accessing dynamic array elements
    }
    cout << endl;
    
    delete[] dynamicArray; // Free the allocated memory for the array

    // Smart pointers
    // Using unique_ptr
    unique_ptr<int> uniquePtr(new int(100)); // Allocate using unique_ptr
    cout << "Value in unique_ptr: " << *uniquePtr << endl;

    // Using shared_ptr
    shared_ptr<int> sharedPtr1(new int(200)); // Allocate using shared_ptr
    {
        shared_ptr<int> sharedPtr2 = sharedPtr1; // Shared ownership
        cout << "Value in shared_ptr: " << *sharedPtr2 << endl;
        cout << "Shared reference count: " << sharedPtr2.use_count() << endl;
    }
    cout << "Shared reference count after sharedPtr2 goes out of scope: " << sharedPtr1.use_count() << endl;

    // Using weak_ptr
    weak_ptr<int> weakPtr = sharedPtr1; // Create a weak_ptr from shared_ptr
    cout << "Is weak_ptr expired? " << (weakPtr.expired() ? "Yes" : "No") << endl;

    if (auto sharedPtr3 = weakPtr.lock()) { // Lock to get a shared_ptr
        cout << "Value in weak_ptr: " << *sharedPtr3 << endl;
    } else {
        cout << "weak_ptr is expired!" << endl;
    }

    return 0;
}
