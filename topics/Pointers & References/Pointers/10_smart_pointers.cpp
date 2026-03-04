#include <iostream>
#include <memory>

int main() {
    std::unique_ptr<int> p1(new int(10)); // Unique pointer
    std::cout << "Value: " << *p1 << std::endl;

    std::shared_ptr<int> p2 = std::make_shared<int>(20); // Shared pointer
    std::shared_ptr<int> p3 = p2; // p2 and p3 now share ownership

    std::cout << "Value: " << *p2 << ", Count: " << p2.use_count() << std::endl;

    return 0;
}
