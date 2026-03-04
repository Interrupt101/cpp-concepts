/*
    Difference between push_back & emplace_back for vectors
*/
#include <iostream>
#include <vector>
#include <string>

class Person {
public:
    std::string name;
    int age;

    // Constructor
    Person(const std::string& n, int a) : name(n), age(a) {
        std::cout << "Constructing Person: " << name << std::endl;
    }

    // Copy constructor
    Person(const Person& other) : name(other.name), age(other.age) {
        std::cout << "Copy Constructing Person: " << name << std::endl;
    }

    // Move constructor
    Person(Person&& other) noexcept : name(std::move(other.name)), age(other.age) {
        std::cout << "Move Constructing Person: " << name << std::endl;
    }
};

int main() {
    std::vector<Person> people0;

    // Using push_back
    std::cout << "\nUsing push_back:\n";
    people0.push_back(Person("Alice", 30));
	
	/*
	Output :	
		Using push_back:
		Constructing Person: Alice
		Move Constructing Person: Alice
	*/

	std::vector<Person> people1;
    // Using emplace_back
    std::cout << "\nUsing emplace_back:\n";
    people1.emplace_back("Bob", 25);
	
	/*
	Output :
		Using emplace_back:
		Constructing Person: Bob
	*/

    return 0;
}
