#include <iostream>

int main() {
    int arr[3] = {10, 20, 30};
    int* p = arr;

    for(int i = 0; i < 3; i++) {
        std::cout << "arr[" << i << "] = " << arr[i] << ", *(p + " << i << ") = " << *(p + i) << std::endl;
    }

    return 0;
}
