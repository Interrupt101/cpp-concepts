#include<iostream>
#include<memory>

class Car
{
public:
	Car();
	~Car();
	void Show();
};

Car::Car(){
	std::cout << "Car constructed succussfully!" << std::endl;
}

Car::~Car(){
	std::cout << "Car destructed succussfully!" << std::endl;
}

void Car::Show(){
	std::cout << "Show car called!" << std::endl;
}

int main()
{
	std::unique_ptr<Car> ptr1 = std::make_unique<Car>();
	ptr1->Show();

	std::unique_ptr<Car> ptr2 = std::move(ptr1);
	if(!ptr1){
		std::cout << "ptr1 is now null!\n";
	}
	ptr2->Show();
	
	return 0;
	
}



