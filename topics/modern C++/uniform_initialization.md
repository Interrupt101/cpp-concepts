Uniform initialization in C++ is a syntax introduced with C++11 to provide a consistent and uniform way to initialize variables and objects. It uses curly braces {} for initialization and helps reduce ambiguities, especially with constructors, providing clearer code.

### Key Features:
1 - Consistent Syntax: You can use {} to initialize variables of any type, including primitives, classes, arrays, and containers.

 ```cpp
int x{10};             // Primitive type
std::vector<int> vec{1, 2, 3};  // Initializing a vector with values
 ```
2 - Prevents Narrowing Conversions: One of the most important features of uniform initialization is that it prohibits "narrowing conversions" (where precision may be lost).
 ```cpp
int a = 3.5;        // Allowed in traditional initialization
int b{3.5};         // Error in uniform initialization (narrowing)
```
3 - Initialization of Aggregate Types: Structs and arrays can be initialized easily using uniform initialization.
 
 ```cpp
struct Point {
    int x;
    int y;
};
 
Point p{10, 20};  // Initializes p.x = 10, p.y = 20
```
4 - Works with Constructors: If a class has a constructor, uniform initialization can be used to call that constructor.

 ```cpp
class MyClass {
public:
    MyClass(int a, int b) { /*...*/ }
};

MyClass obj{1, 2};  // Calls MyClass(int, int) constructor
```
