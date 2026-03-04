#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass constructed\n"; }
    ~MyClass() { std::cout << "MyClass destructed\n"; }
    void show() { std::cout << "MyClass::show() called\n"; }
};

int main() {
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    ptr1->show();
    
    {
        std::shared_ptr<MyClass> ptr2 = ptr1; // ptr2 shares ownership with ptr1
        ptr2->show();
        std::cout << "Use count: " << ptr1.use_count() << "\n"; // Output: 2
    } // ptr2 goes out of scope, but object is not destroyed because ptr1 still exists

    std::cout << "Use count after ptr2 is out of scope: " << ptr1.use_count() << "\n"; // Output: 1
    // Object is destroyed when ptr1 goes out of scope

    return 0;
}
