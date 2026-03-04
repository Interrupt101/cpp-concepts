// file_handling.cpp
// File Handling in C++

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // File streams: ifstream for reading, ofstream for writing, fstream for both
    string filename = "example.txt";
    
    // Writing to a file
    ofstream outFile(filename);
    if (!outFile) { // Error handling
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }

    outFile << "Hello, World!" << endl; // Writing to the file
    outFile << "This is a test file for file handling in C++." << endl;
    outFile.close(); // Close the file after writing

    // Reading from a file
    ifstream inFile(filename);
    if (!inFile) { // Error handling
        cerr << "Error opening file for reading!" << endl;
        return 1;
    }

    string line;
    cout << "Contents of the file:" << endl;
    while (getline(inFile, line)) { // Reading line by line
        cout << line << endl;
    }
    inFile.close(); // Close the file after reading

    return 0;
}
