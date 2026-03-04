// arrays.cpp
// Working with Arrays in C++

#include <iostream>
using namespace std;

int main() {

    // Definition and syntax
    int numbers[5]; // Declare an array of 5 integers

    // Accessing array elements
    numbers[0] = 10;   // Assign values to array elements
    numbers[1] = 20;
    numbers[2] = 30;
    numbers[3] = 40;
    numbers[4] = 50;

    cout << "Array elements:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << numbers[i] << " "; // Accessing array elements
    }
    cout << endl;

    // Multi-dimensional arrays
    int matrix[2][3] = { {1, 2, 3}, {4, 5, 6} }; // 2x3 matrix

    cout << "2x3 Matrix elements:" << endl;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " "; // Accessing multi-dimensional array elements
        }
        cout << endl;
    }

    return 0;
}
