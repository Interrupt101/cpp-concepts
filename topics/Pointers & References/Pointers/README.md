# Pointers in C++

## Overview

Pointers are a fundamental concept in C++ that allow you to directly work with memory by storing and manipulating the address of variables. Understanding pointers is crucial for effective memory management, dynamic memory allocation, and efficient function handling.

This folder contains examples and explanations of various pointer concepts in C++.

## Table of Contents

1. [Basics of Pointers](01_basics_of_pointers.cpp)
2. [Pointer Arithmetic](02_pointer_arithmetic.cpp)
3. [Pointers to Pointers](03_pointer_to_pointer.cpp)
4. [Pointers and Arrays](04_pointers_and_arrays.cpp)
5. [Pointers and Functions](05_pointers_and_functions.cpp)
6. [Void Pointers](06_void_pointers.cpp)
7. [Null and Dangling Pointers](07_null_and_dangling_pointers.cpp)
8. [Constant Pointers](08_const_pointers.cpp)
9. [Function Pointers](09_function_pointers.cpp)
10. [Smart Pointers (Modern C++)](10_smart_pointers.cpp)

## 1. Basics of Pointers

This section introduces pointers, explaining what they are, how to declare them, and how to use them to store the address of variables. [View Code](01_basics_of_pointers.cpp)

## 2. Pointer Arithmetic

Pointers can be incremented or decremented to point to the next or previous memory location. This section demonstrates how pointer arithmetic works. [View Code](02_pointer_arithmetic.cpp)

## 3. Pointers to Pointers

A pointer can also point to another pointer, which is known as a double pointer. This concept is essential in scenarios like dynamic memory allocation. [View Code](03_pointer_to_pointer.cpp)

## 4. Pointers and Arrays

This section explains the relationship between pointers and arrays, showing how pointers can be used to navigate through array elements. [View Code](04_pointers_and_arrays.cpp)

## 5. Pointers and Functions

Pointers can be used to pass arguments to functions by reference, allowing the function to modify the original variables. [View Code](05_pointers_and_functions.cpp)

## 6. Void Pointers

Void pointers are generic pointers that can point to any data type, but they must be cast to the correct type before dereferencing. [View Code](06_void_pointers.cpp)

## 7. Null and Dangling Pointers

Null pointers point to nothing and are often used as a sentinel value. Dangling pointers occur when a pointer still references a memory location that has been freed. [View Code](07_null_and_dangling_pointers.cpp)

## 8. Constant Pointers

This section covers pointers that are constant, meaning the pointer itself or the data it points to cannot be modified. [View Code](08_const_pointers.cpp)

## 9. Function Pointers

Function pointers are pointers that point to the address of a function. This is useful for callback functions and implementing function tables. [View Code](09_function_pointers.cpp)

## 10. Smart Pointers (Modern C++)

Smart pointers, introduced in C++11, automatically manage memory, reducing the risk of memory leaks. This section introduces `std::unique_ptr` and `std::shared_ptr`. [View Code](10_smart_pointers.cpp)



---

Each file in this repository provides a simple, self-contained example of the concept being discussed. Feel free to explore the code, run the examples, and modify them to deepen your understanding of pointers in C++.
