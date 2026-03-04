// cpp_variable_scope_lifetime.cpp
// This program demonstrates the concepts of variable scope and lifetime in C++.

#include <iostream>

using namespace std;

/*
    Variable Scope:
    Scope defines the region of the program where a variable is accessible.
    C++ has several types of scopes:
    1. Block Scope
    2. Function Scope
    3. Global Scope
    4. Class Scope

    Variable Lifetime:
    Lifetime refers to the duration for which a variable exists in memory.
    Different storage durations in C++ determine the lifetime of variables:
    1. Automatic Storage Duration
    2. Static Storage Duration
    3. Dynamic Storage Duration
*/

// 1. Block Scope
void blockScopeExample() {
    cout << "Entering blockScopeExample()\n";

    if (true) { // Start of a new block
        int x = 10; // 'x' has block scope
        cout << "Inside block: x = " << x << endl;
    } // 'x' is destroyed here

    // Uncommenting the next line would cause a compilation error because 'x' is out of scope
    // cout << x;

    cout << "Exiting blockScopeExample()\n\n";
}

// 2. Function Scope
int globalVar = 100; // Global variable

void functionScopeExample() {
    cout << "Entering functionScopeExample()\n";
    // 'globalVar' is accessible here
    cout << "Global variable: globalVar = " << globalVar << endl;
    cout << "Exiting functionScopeExample()\n\n";
}

// 3. Global Scope
int globalScopeVar = 200; // Accessible throughout the file after its declaration

void globalScopeAccess() {
    cout << "Accessing globalScopeVar from globalScopeAccess(): " << globalScopeVar << endl;
}

// 4. Class Scope
class MyClass {
public:
    int memberVar;

    MyClass(int val) : memberVar(val) {
        cout << "MyClass constructor called. memberVar = " << memberVar << endl;
    }

    void display() {
        cout << "MyClass memberVar: " << memberVar << endl;
    }
};

// Variable Lifetime Examples

// Automatic Storage Duration
void automaticLifetime() {
    cout << "Entering automaticLifetime()\n";
    int autoVar = 300; // 'autoVar' is created here
    cout << "autoVar = " << autoVar << endl;
    // 'autoVar' is destroyed when the function returns
    cout << "Exiting automaticLifetime()\n\n";
}

// Static Storage Duration
void staticLifetime() {
    cout << "Entering staticLifetime()\n";
    static int staticVar = 400; // 'staticVar' is initialized only once
    cout << "staticVar = " << staticVar << endl;
    staticVar++;
    cout << "staticVar after increment = " << staticVar << endl;
    // 'staticVar' exists until the program ends
    cout << "Exiting staticLifetime()\n\n";
}

// Dynamic Storage Duration
void dynamicLifetime() {
    cout << "Entering dynamicLifetime()\n";
    int* dynVar = new int(500); // 'dynVar' points to dynamically allocated memory
    cout << "*dynVar = " << *dynVar << endl;
    delete dynVar; // Memory is freed here
    // 'dynVar' pointer is destroyed when it goes out of scope, but the allocated memory must be freed manually
    cout << "Exiting dynamicLifetime()\n\n";
}

int main() {
    cout << "Variable Scope and Lifetime Demonstration in C++\n\n";

    // Demonstrate Block Scope
    blockScopeExample();

    // Demonstrate Function Scope (accessing global variable)
    functionScopeExample();

    // Demonstrate Global Scope
    globalScopeAccess();

    // Demonstrate Class Scope
    MyClass obj(600);
    obj.display();

    // Demonstrate Variable Lifetime
    automaticLifetime();
    staticLifetime();
    staticLifetime(); // Static variable retains its value between calls
    dynamicLifetime();

    return 0;
}
