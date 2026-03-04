#include <iostream>
#include <deque>

int main() {
    // Declare a 2D deque
    std::deque<std::deque<int>> matrix = {{1, 2, 3}, {4, 5, 6}};

    // Access elements
    std::cout << "Matrix elements:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    // Modify elements
    matrix[0][0] = 10;
    matrix[1][2] = 60;

    // Print modified matrix
    std::cout << "Modified matrix elements:" << std::endl;
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
