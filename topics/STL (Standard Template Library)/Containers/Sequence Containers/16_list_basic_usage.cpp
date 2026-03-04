#include <iostream>
#include <list>

int main()
{
    std::list<int> myList = {1, 5, 6, 8, 3, 1};
    std::cout << "Printing my list";
    for(int n : myList)
    {
        std::cout << n << ' ';
    }
    std::cout << std::endl;

    myList.push_back(6); // Add to the end
    myList.push_front(0); // Add to the beginning

    std::cout << "After adding elements: ";
    for (int n : myList) {
        std::cout << n << ' ';
    }

    std::cout << std::endl;

    myList.pop_back(); // Remove from the end
    myList.pop_front(); // Remove from the beginning

    for (int n : myList) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;
    
    return 0;
}