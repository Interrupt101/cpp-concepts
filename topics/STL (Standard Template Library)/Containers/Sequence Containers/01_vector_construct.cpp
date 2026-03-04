#include <iostream>
#include <vector>

int main() {
    // 1. Default constructor: Creates an empty vector.
    std::vector<int> vec1;
    std::cout << "Size of vec1: " << vec1.size() << std::endl;

    // 2. Fill constructor: Creates a vector with 10 elements, each initialized to 5.
    std::vector<int> vec2(10, 5);
    std::cout << "Elements of vec2: ";
    for (int val : vec2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 3. Range constructor: Creates a vector from elements in the range [first, last).
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec3(arr, arr + 5);
    std::cout << "Elements of vec3: ";
    for (int val : vec3) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 4. Copy constructor: Creates a vector as a copy of another vector.
    std::vector<int> vec4(vec3);
    std::cout << "Elements of vec4 (copy of vec3): ";
    for (int val : vec4) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 5. Move constructor: Creates a vector by moving resources from another vector.
    std::vector<int> vec5(std::move(vec4));
    std::cout << "Elements of vec5 (moved from vec4): ";
    for (int val : vec5) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    std::cout << "Size of vec4 after move: " << vec4.size() << std::endl;

    // 6. Initializer list constructor: Creates a vector from an initializer list.
    std::vector<int> vec6 = {10, 20, 30, 40, 50};
    std::cout << "Elements of vec6: ";
    for (int val : vec6) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // 7. Using emplace_back to construct elements in-place.
    std::vector<std::pair<int, int>> vec7;
    vec7.emplace_back(1, 2);  // Constructs a pair<int, int>(1, 2) in-place.
    vec7.emplace_back(3, 4);
    std::cout << "Elements of vec7: ";
    for (const auto& pair : vec7) {
        std::cout << "(" << pair.first << ", " << pair.second << ") ";
    }
    std::cout << std::endl;

    return 0;
}
