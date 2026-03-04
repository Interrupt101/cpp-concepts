#include<iostream>

extern "C" {
	__declspec(dllexport) void hello() { // mark the function as exportable
		std::cout << "Hello World!" << std::endl;
	}
}
