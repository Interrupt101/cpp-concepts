# Reference Type
## When they were introduced?
- Introduced in C++98
## What are reference types
- Defines an alternative name for a variable (an alias)
- It is created with the & operator during declaration
- Always needs an initializer!
- It can be used to modify a variable like pointer
- A reference is NOT a new variable; it is just another name
- They have both same memory address
## Why they were introduced?
- safer because they must always refer to valid objects.
## Difference between a pointer & a reference
- Reference : needs initializer, cannot be nullptr, boud to its referent, no storage required. 
- Pointer : no need for initializer, can be nullptr, can point other variables, has it's own storage.

# Name mangling 
- Name mangling in C++ refers to the process by which the compiler modifies the names of functions, variables, or other identifiers to encode additional information about them
## Why is Mangling Needed?
- In C (and similar languages), functions have unique names, so there's no ambiguity when linking them. However, C++ allows:
- Function overloading: Multiple functions can have the same name but different parameter types.
- Namespaces: Identifiers can be scoped inside different namespaces.
- g++ -o myprogram myprogram.cpp -Wl,-Map=myprogram.map
- nm is a Unix/Linux command-line utility used to display the symbol table of object file
- nm myprogram | c++filt to demangle

# Function Pointer
- Pointer that holds the address of a function
- The type is same as the signature of the function (return type & arguments)
- Can be used to indirectly invoke a function even if the function name is not known
- used by algorithms and classes for optimization
- \<ret\> (*fnptr)args = &function

# Default Copy Constructor (Shallow Copy)
If you do not explicitly define a copy constructor, the C++ compiler provides a default copy constructor that performs a shallow copy.
## Example of Default Shallow Copy
```cpp
class Shallow {
public:
    int *data;

    Shallow(int value) {
        data = new int;
        *data = value;
    }
};

int main() {
    Shallow obj1(10);
    Shallow obj2 = obj1; // Default copy constructor (shallow copy)

    // Both obj1.data and obj2.data point to the same memory
    *obj2.data = 20;

    // Now, obj1.data also reflects the change
    std::cout << *obj1.data; // Outputs: 20

    delete obj1.data; // Deleting data affects both obj1 and obj2
    return 0;
}
```
## Issues with Shallow Copy:
- Shared Resources: Both objects share the same dynamically allocated memory.
- Double Deletion: If both objects try to delete the same memory, it leads to undefined behavior.

# Implementing a Deep Copy
To perform a deep copy, you need to define your own copy constructor that allocates separate memory for the copied object and copies the actual data.
## Example of Deep Copy
```cpp
class Deep {
public:
    int *data;

    // Constructor
    Deep(int value) {
        data = new int;
        *data = value;
    }

    // Copy Constructor (Deep Copy)
    Deep(const Deep &other) {
        data = new int;          // Allocate new memory
        *data = *(other.data);   // Copy the value
    }

    // Destructor
    ~Deep() {
        delete data;
    }
};

int main() {
    Deep obj1(10);
    Deep obj2 = obj1; // Calls deep copy constructor

    *obj2.data = 20;

    std::cout << *obj1.data; // Outputs: 10
    std::cout << *obj2.data; // Outputs: 20

    // No double deletion issue since obj1 and obj2 have separate memory
    return 0;
}
```
## When to Use Deep Copy
Use a deep copy when your class manages resources that require ownership, such as:
- Dynamic Memory Allocation: If your class allocates memory using new, malloc, etc.
- File Handles or Network Connections: When your class manages resources like file descriptors, sockets, etc.
- Complex Data Structures: When your class contains complex members that require independent copies.


# Delegating Constructors (C++11)
- Allows a constructor to call another constructor
- Replacement for common initialization
- Reduces duplicate initialization code in multiple constructors
```cpp
#include <iostream>
#include <string>

class Person {
private:
    std::string name;
    int age;

public:
    // Constructor that takes both name and age
    Person(const std::string& name, int age) : name(name), age(age) {
        std::cout << "Person created with name and age\n";
    }

    // Delegating constructor that only takes a name, assumes a default age
    Person(const std::string& name) : Person(name, 0) { // Delegates to the constructor above
        std::cout << "Person created with name only\n";
    }

    // Delegating constructor that takes no arguments, assumes default values
    Person() : Person("Unknown", 0) { // Delegates to the constructor above
        std::cout << "Person created with no details\n";
    }

    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << '\n';
    }
};

int main() {
    Person p1("Alice", 25);  // Calls the first constructor
    Person p2("Bob");        // Calls the second constructor, which delegates to the first
    Person p3;               // Calls the third constructor, which delegates to the first

    p1.display();
    p2.display();
    p3.display();

    return 0;
}
```

# default & deleted (C++11) 
```cpp
#include <iostream>

class Example {
public:
    // Constructor is explicitly defaulted
    Example() = default;

    // Copy constructor is deleted, preventing object copying
    Example(const Example&) = delete;

    // Assignment operator is also deleted
    Example& operator=(const Example&) = delete;

    void setValue(int a) {}
    void setValue(float) = delete;

    // Destructor is explicitly defaulted
    ~Example() = default;
};

int main() {
    Example obj1;    // This is allowed: default constructor is available.

    // Example obj2 = obj1;   // Error: Copy constructor is deleted.
    // obj1 = obj2;           // Error: Assignment operator is deleted.

    Example ex1;
    ex1.setValue(4);
    ex1.setValue(4.1); // will not be invoked!

    return 0;
}
```