#include <iostream>

int main() {
    int* p = nullptr; // Null pointer

    if (p == nullptr) {
        std::cout << "Pointer is null" << std::endl;
    }

    // Dangling pointer example
    int* q = new int(10);
    delete q;
    q = nullptr; // Avoid dangling pointer by setting it to null after delete

    return 0;
}
