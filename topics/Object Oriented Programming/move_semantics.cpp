/*
What is a Move Constructor?
    In C++, a move constructor is a special constructor used to "move" resources from one object to another, 
    rather than copying them. This is particularly useful for optimizing performance by avoiding unnecessary 
    deep copies, especially for objects managing dynamic resources like memory, file handles, 
    or network connections.

Why Do We Need a Move Constructor?
    When you pass objects around in your program (like returning an object from a function or passing it 
    to a function), the default behavior involves copying the object, which can be expensive if the object 
    manages resources like large arrays or other dynamic memory.
*/

#include <iostream>
#include <utility> // For std::move

class MyClass {
private:
    int* data;
public:
    // Constructor
    MyClass(int value) {
        data = new int(value);
        std::cout << "Constructor called\n";
    }

    // Move Constructor
    MyClass(MyClass&& other) noexcept   // noexcept : doesn't throw exception (good for optimizations)
        : data(other.data) {
        other.data = nullptr; // Nullify the source pointer
        std::cout << "Move Constructor called\n";
    }

    // Destructor
    ~MyClass() {
        delete data;
        std::cout << "Destructor called\n";
    }

    // Copy Constructor (disabled)
    MyClass(const MyClass& other) = delete;

    // Copy Assignment Operator (disabled)
    MyClass& operator=(const MyClass& other) = delete;

    // Move Assignment Operator
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete data; // Release current resource
            data = other.data; // Transfer ownership
            other.data = nullptr; // Nullify the source pointer
        }
        std::cout << "Move Assignment called\n";
        return *this;
    }

    void display() const {
        if (data)
            std::cout << "Value: " << *data << "\n";
        else
            std::cout << "Data is null\n";
    }
};

int main() {
    MyClass obj1(42);         // Constructor
    MyClass obj2(std::move(obj1)); // Move Constructor

    obj2.display();
    obj1.display();           // Data is null

    MyClass obj3(100);
    obj3 = std::move(obj2);   // Move Assignment
    obj3.display();
    obj2.display();           // Data is null

    return 0;
}
