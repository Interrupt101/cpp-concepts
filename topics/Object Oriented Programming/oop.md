# Introduction to Object-Oriented Programming (OOP) in C++

## What is OOP?
Object-Oriented Programming (OOP) is a programming paradigm that is based on the concept of "objects". Objects are instances of classes, which encapsulate data (attributes) and functions (methods) that operate on that data. OOP aims to provide a more intuitive way of organizing and structuring code, making it easier to maintain, reuse, and extend.

### Four Core Concepts of OOP:
1. **Encapsulation**: Bundling of data and methods that manipulate the data into a single unit (class).
2. **Abstraction**: Hiding the internal implementation and only exposing the functionality.
3. **Inheritance**: The ability to create new classes from existing classes to reuse and extend functionality.
4. **Polymorphism**: The ability to use the same interface for different data types or classes.

---

## Class and Object in C++

A **class** is a blueprint for creating objects. An **object** is an instance of a class.

### Syntax:
```cpp
class ClassName {
public:
    // Attributes (data members)
    int attribute;

    // Methods (member functions)
    void display() {
        std::cout << "Attribute value: " << attribute << std::endl;
    }
};

int main() {
    ClassName obj;      // Creating an object
    obj.attribute = 5;  // Accessing attribute
    obj.display();      // Calling method
    return 0;
}
```
### Explanation:
- ClassName: Defines the class.
- obj: An object of type ClassName.
- attribute: A public attribute of the class.
- display(): A method that prints the value of the attribute.

## Encapsulation in C++
Encapsulation is achieved by keeping data members private and providing public methods to access and modify them.

### Example:
```cpp
class Person {
private:
    std::string name;
    int age;

public:
    void setName(std::string n) {
        name = n;
    }

    void setAge(int a) {
        if (a >= 0) {  // Basic validation
            age = a;
        }
    }

    void display() {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main() {
    Person p;
    p.setName("John");
    p.setAge(25);
    p.display();
    return 0;
}
```

### Explanation:
- name and age are private and cannot be accessed directly from outside the class.
- Public methods setName() and setAge() provide controlled access to these private members.

## Inheritance in C++
Inheritance allows one class to inherit properties and behavior from another class.

### Example:
```cpp
class Animal {
public:
    void speak() {
        std::cout << "Animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void speak() {
        std::cout << "Bark!" << std::endl;
    }
};

int main() {
    Animal a;
    Dog d;
    
    a.speak();  // Output: Animal sound
    d.speak();  // Output: Bark!
    return 0;
}
```
### Explanation:
- Dog class inherits from Animal.
- The Dog class overrides the speak() method of the Animal class.

## Polymorphism in C++
Polymorphism in C++ is achieved through function overriding or overloading, and through pointers and references to base classes.

### Example: Runtime Polymorphism (Function Overriding)
```cpp
class Animal {
public:
    virtual void speak() {
        std::cout << "Animal sound" << std::endl;
    }
};

class Dog : public Animal {
public:
    void speak() override {
        std::cout << "Bark!" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() override {
        std::cout << "Meow!" << std::endl;
    }
};

int main() {
    Animal* animal1 = new Dog();
    Animal* animal2 = new Cat();

    animal1->speak();  // Output: Bark!
    animal2->speak();  // Output: Meow!

    delete animal1;
    delete animal2;
    return 0;
}
```
### Explanation:
- The speak() method is marked virtual in the base class Animal to enable polymorphism.
- The Dog and Cat classes override the speak() method to provide specific behavior.
- At runtime, the correct method is invoked based on the actual object type (either Dog or Cat).

## Abstraction in C++
Abstraction focuses on exposing only the essential details while hiding the implementation details. It is commonly achieved using abstract classes and interfaces.

### Example:
```cpp
class Shape {
public:
    virtual void draw() = 0;  // Pure virtual function
};

class Circle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Circle" << std::endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Drawing Rectangle" << std::endl;
    }
};

int main() {
    Shape* shape1 = new Circle();
    Shape* shape2 = new Rectangle();

    shape1->draw();  // Output: Drawing Circle
    shape2->draw();  // Output: Drawing Rectangle

    delete shape1;
    delete shape2;
    return 0;
}
```
### Explanation:
- Shape is an abstract class with a pure virtual function draw().
- Circle and Rectangle are concrete classes that implement the draw() function.
