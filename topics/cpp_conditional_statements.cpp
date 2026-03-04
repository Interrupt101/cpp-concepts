// conditional_statements.cpp
// Conditional Statements in C++

#include <iostream>
using namespace std;

int main() {
    int num;

    // If, else if, else
    cout << "Enter a number: ";
    cin >> num;

    if (num > 0) {
        cout << num << " is positive." << endl;
    }
    else if (num < 0) {
        cout << num << " is negative." << endl;
    }
    else {
        cout << "The number is zero." << endl;
    }

    // Nested conditions
    int a = 10, b = 20;
    if (a > 0) {
        if (b > a) {
            cout << "b is greater than a and a is positive." << endl;
        }
    }

    // Switch case
    int choice;
    cout << "Choose a number between 1 and 3: ";
    cin >> choice;

    switch (choice) {
        case 1:
            cout << "You chose 1." << endl;
            break;
        case 2:
            cout << "You chose 2." << endl;
            break;
        case 3:
            cout << "You chose 3." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
