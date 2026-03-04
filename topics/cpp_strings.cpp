// strings.cpp
// Working with Strings in C++

#include <iostream>
#include <cstring>   // For C-style string functions
#include <string>    // For std::string
using namespace std;

int main() {

    // Character arrays (C-strings)
    char cstr[20];              // Declare a C-string (character array)
    strcpy(cstr, "Hello C++!");  // Copy a string into the C-string
    cout << "C-string: " << cstr << endl;

    // Introduction to std::string
    string cppStr = "Hello, std::string!"; // Declare and initialize a C++ string
    cout << "C++ string: " << cppStr << endl;

    // String functions
    // Length of the string
    cout << "Length of C++ string: " << cppStr.length() << endl;

    // Substring
    string subStr = cppStr.substr(0, 5); // Extract substring from index 0 to 4
    cout << "Substring: " << subStr << endl;

    // Find a substring
    size_t pos = cppStr.find("std");
    if (pos != string::npos) {
        cout << "'std' found at index: " << pos << endl;
    } else {
        cout << "'std' not found!" << endl;
    }

    // Concatenation
    string concatenatedStr = cppStr + " Concatenation example!";
    cout << "Concatenated string: " << concatenatedStr << endl;

    return 0;
}
