#include <iostream>

int& getElement(int arr[], int index) {
    return arr[index]; // Returns a reference to the element
}

int main() {
    int arr[3] = {10, 20, 30};

    getElement(arr, 1) = 50; // Modifies the array directly
    std::cout << "arr[1] after modification: " << arr[1] << std::endl;

    return 0;
}
