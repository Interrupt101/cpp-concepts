#include <iostream>
#include <string>
using namespace std;

// Function Declaration and Definition
// Syntax: return_type function_name(parameters) { function_body; }

// 1. Simple function with no parameters and no return value
void sayHello() {
    cout << "Hello, World!" << endl;
}

// 2. Function with parameters
void greetUser(string name) {
    cout << "Hello, " << name << "!" << endl;
}

// 3. Function with return value
int add(int a, int b) {
    return a + b;
}

// 4. Function with default parameters
void displayInfo(string name = "User", int age = 18) {
    cout << "Name: " << name << ", Age: " << age << endl;
}

// 5. Function Overloading - Same function name, but different parameters
int multiply(int a, int b) {
    return a * b;
}

double multiply(double a, double b) {
    return a * b;
}

// 6. Pass by Value - The original value is not modified
void incrementValue(int num) {
    num++;
    cout << "Inside function: " << num << endl; // Shows incremented value
}

// 7. Pass by Reference - The original value is modified
void incrementReference(int &num) {
    num++;
    cout << "Inside function: " << num << endl; // Shows incremented value
}

// 8. Recursive Function - Function that calls itself
int factorial(int n) {
    if (n <= 1) {
        return 1; // Base case
    }
    return n * factorial(n - 1); // Recursive call
}

// Main function
int main() {
    // 1. Calling a simple function
    sayHello();

    // 2. Function with parameters
    greetUser("Alice");

    // 3. Function with return value
    int sum = add(5, 7);
    cout << "Sum: " << sum << endl;

    // 4. Function with default parameters
    displayInfo(); // Uses default values
    displayInfo("Bob", 25); // Overrides default values

    // 5. Function Overloading
    cout << "Multiplication (int): " << multiply(3, 4) << endl;
    cout << "Multiplication (double): " << multiply(2.5, 4.5) << endl;

    // 6. Pass by Value
    int number = 10;
    incrementValue(number);
    cout << "After function call (pass by value): " << number << endl; // Original value remains unchanged

    // 7. Pass by Reference
    incrementReference(number);
    cout << "After function call (pass by reference): " << number << endl; // Value is changed

    // 8. Recursive Function
    int fact = factorial(5);
    cout << "Factorial of 5: " << fact << endl;

    return 0;
}
