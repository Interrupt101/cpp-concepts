// structures_and_unions.cpp
// Structures and Unions in C++

#include <iostream>
using namespace std;

// Defining a structure
struct Point {
    int x;
    int y;
};

// Function that uses a structure
void printPoint(const Point& p) {
    cout << "Point(" << p.x << ", " << p.y << ")" << endl;
}

// Defining a union
union Data {
    int intValue;
    float floatValue;
    char charValue;
};

// Enum definition
enum Color {
    RED,
    GREEN,
    BLUE
};

// Enum class definition (C++11)
enum class Direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

int main() {
    // Using structures
    Point p1;                  // Declare a Point structure
    p1.x = 10;                 // Assign values
    p1.y = 20;
    printPoint(p1);           // Call function using structure

    // Using unions
    Data data;                // Declare a union
    data.intValue = 5;       // Assign integer value
    cout << "Union intValue: " << data.intValue << endl;

    data.floatValue = 3.14;  // Assign float value (overwrites intValue)
    cout << "Union floatValue: " << data.floatValue << endl;

    // Note: Accessing intValue after assigning floatValue leads to undefined behavior
    // cout << "Union intValue after float assignment: " << data.intValue << endl; // Undefined behavior

    // Using enum
    Color myColor = GREEN;    // Assign enum value
    if (myColor == GREEN) {
        cout << "The color is GREEN." << endl;
    }

    // Using enum class
    Direction myDirection = Direction::NORTH; // Assign enum class value
    if (myDirection == Direction::NORTH) {
        cout << "The direction is NORTH." << endl;
    }

    return 0;
}
