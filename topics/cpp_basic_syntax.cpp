// cpp_basic_syntax.cpp
// Basic Syntax in C++

#include <iostream> // Required for cin, cout
using namespace std;

int main() {

    // Comments in C++
    // Single-line comment

    /* 
       Multi-line comment
    */

    // Data Types
    int integer = 10;             // Integer data type
    float decimal = 3.14f;        // Float data type
    char character = 'A';         // Character data type
    bool is_true = true;          // Boolean data type (true or false)

    // Variables and Constants
    int num = 20;                 // Variable (value can be changed)
    const float PI = 3.14159;     // Constant (value cannot be changed)

    // Input/Output
    cout << "Enter a number: ";
    int userInput;
    cin >> userInput;             // Taking input from the user
    cout << "You entered: " << userInput << endl; // Outputting the result

    // Operators
    // Arithmetic Operators: +, -, *, /, %
    int a = 10, b = 3;
    cout << "a + b = " << a + b << endl;   // Addition
    cout << "a - b = " << a - b << endl;   // Subtraction
    cout << "a * b = " << a * b << endl;   // Multiplication
    cout << "a / b = " << a / b << endl;   // Division
    cout << "a % b = " << a % b << endl;   // Modulus

    // Logical Operators: && (AND), || (OR), ! (NOT)
    bool condition = (a > b) && (a != 0);  // Logical AND
    cout << "Logical AND (a > b && a != 0): " << condition << endl;

    condition = (a < b) || (a == 10);      // Logical OR
    cout << "Logical OR (a < b || a == 10): " << condition << endl;

    condition = !(a == 10);                // Logical NOT
    cout << "Logical NOT !(a == 10): " << condition << endl;

    // Relational Operators: ==, !=, >, <, >=, <=
    cout << "Is a equal to b? " << (a == b) << endl;   // Equality
    cout << "Is a not equal to b? " << (a != b) << endl; // Inequality
    cout << "Is a greater than b? " << (a > b) << endl;  // Greater than
    cout << "Is a less than or equal to b? " << (a <= b) << endl; // Less than or equal to

    return 0;
}
