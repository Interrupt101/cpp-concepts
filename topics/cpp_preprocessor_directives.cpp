// preprocessor_directives.cpp
// Preprocessor Directives in C++

#include <iostream>
using namespace std;

// Macro definition using #define
#define SQUARE(x) ((x) * (x)) // Macro to calculate the square of a number

// Conditional compilation
#define DEBUG // Uncomment to enable debug mode

int main() {
    // Using #include to include the iostream header
    cout << "Preprocessor Directives Example" << endl;

    // Using the defined macro
    int num = 5;
    cout << "Square of " << num << " is " << SQUARE(num) << endl;

    // Conditional compilation
#ifdef DEBUG
    cout << "Debug mode is enabled." << endl; // This will be included if DEBUG is defined
#else
    cout << "Debug mode is disabled." << endl; // This will be included if DEBUG is not defined
#endif

    // Using #pragma directives
#pragma message("This is a message from the preprocessor.") // Display a message during compilation
#pragma once // Ensure the header file is included only once (useful in header files)

    return 0;
}
