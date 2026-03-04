
// loops.cpp
// Loops in C++

#include <iostream>
using namespace std;

int main() {
    // For loop
    cout << "For loop (print numbers from 1 to 5):" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;

    // While loop
    cout << "While loop (print numbers from 1 to 5):" << endl;
    int j = 1;
    while (j <= 5) {
        cout << j << " ";
        j++;
    }
    cout << endl;

    // Do-while loop
    cout << "Do-while loop (print numbers from 1 to 5):" << endl;
    int k = 1;
    do {
        cout << k << " ";
        k++;
    } while (k <= 5);
    cout << endl;

    // Break and continue
    cout << "Break and continue example:" << endl;
    for (int x = 1; x <= 10; x++) {
        if (x == 6) {
            cout << "\nBreaking at " << x << endl;
            break; // Exits the loop when x == 6
        }
        if (x % 2 == 0) {
            continue; // Skips the rest of the loop when x is even
        }
        cout << x << " "; // Only odd numbers will be printed
    }

    return 0;
}
