// calculator.cpp
#include <iostream>
#include <cstdlib> // for std::atof (to convert string to float)
using namespace std;

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 4) {
        cout << "Usage: " << argv[0] << " <number1> <operator> <number2>" << endl;
        return 1; // Return error code if arguments are incorrect
    }

    // Convert the first and third arguments (numbers) from string to double
    double num1 = atof(argv[1]);
    double num2 = atof(argv[3]);

    // Get the operator from the second argument
    char op = argv[2][0];

    // Perform the calculation based on the operator
    double result;
    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
            } else {
                cout << "Error: Division by zero!" << endl;
                return 1; // Return error code for division by zero
            }
            break;
        default:
            cout << "Error: Unsupported operator '" << op << "'!" << endl;
            return 1; // Return error code for invalid operator
    }

    // Output the result
    cout << "Result: " << num1 << " " << op << " " << num2 << " = " << result << endl;

    return 0;
}
