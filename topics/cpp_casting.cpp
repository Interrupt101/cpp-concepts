#include<iostream>

class Base {
public:
	virtual void Show() { std::cout << "Base Class!" << std::endl; }
};
class Derived : public Base {
public:	
	void Show() override { std::cout << "Derived Class!" << std::endl; }
};

int main()
{
	// Implicit casting 
	int i = 10;
	double di = i;
	std::cout << "Implicit casting : " << di << std::endl;
	
	// C-style casting
	double pi = 3.14;
	int intPi = (int)pi;
	std::cout << "C-style cast : " << intPi << std::endl;

	// Static cast :
	int a = 65;
	double d = static_cast<double>(a);
	std::cout << "Static cast : " << d << std::endl;

	// Dynamic cast : 
	// Safely casts pointers or references in a class hierarchy. It performs a runtime check, typically used for polymorphism.
	Base* base = new Base();
	Derived* derived = dynamic_cast<Derived*>(base);
	if(derived) 
		derived->Show();

	// Reinterpret cast
	// Converts between unrelated pointer types with no safety checks. It's used in low-level operations.
	int n = 1;
	char* c = reinterpret_cast<char*>(&n);
	std::cout << "Reinterpret cast : " << static_cast<int>(*c) << std::endl;

	return 0;
}


